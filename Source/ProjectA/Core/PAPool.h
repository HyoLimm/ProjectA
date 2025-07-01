// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Interface.h"
#include "PAPool.generated.h"

UENUM()
enum class EPoolingObjectType : uint8
{
	NONE = 0,
	
	// Actor
	PLAYER_BULLET,
	ENEMY,



	Max
};



class PROJECTA_API FPoolingUObjectHandle
{
	friend class UPAPool;

public:
	FORCEINLINE EPoolingObjectType Type() const	{ return PoolingObjectType; }

	FORCEINLINE UObject* Get() const
	{
		return PoolingObject.IsValid() ? PoolingObject.Get() : nullptr;
	}

	FORCEINLINE UPAPool* GetPool() const
	{
		return PoolObject.IsValid() ? PoolObject.Get() : nullptr;
	}

	FORCEINLINE bool IsValid() const
	{
		return PoolObject.IsValid() && Handle != 0 && PoolingObject.IsValid();
	}

private:
	void Init(UPAPool* InPool, uint64 InHandle, EPoolingObjectType InObjType, UObject* InObject)
	{
		PoolObject = InPool;
		Handle = InHandle;
		PoolingObjectType = InObjType;
		PoolingObject = InObject;
	}

	void Clear()
	{
		PoolObject = nullptr;
		Handle = 0;
		PoolingObjectType = EPoolingObjectType::NONE;
		PoolingObject = nullptr;
	}

private:
	TWeakObjectPtr<UPAPool> PoolObject = nullptr;
	uint64 Handle = 0;
	EPoolingObjectType PoolingObjectType = EPoolingObjectType::NONE;
	TWeakObjectPtr<UObject> PoolingObject = nullptr;
};

UINTERFACE(MinimalAPI)
class UPAPoolingUObject : public UInterface
{
	GENERATED_BODY()
};

class PROJECTA_API IPAPoolingUObject
{
	GENERATED_BODY()
	friend class UPAPool;
protected:
	bool IsManagedPool = false;
	FPoolingUObjectHandle PoolingHandle;
public:

	//bool ReturnPoolingUObject();
	bool CheckManagedPool() const
	{
		return IsManagedPool;
	}
	
	bool CheckCurrentUsing() const
	{
		return PoolingHandle.IsValid();
	}

	FPoolingUObjectHandle* GetPoolingHandle()
	{
		return &PoolingHandle;
	}

	virtual void ConstructFunction() {};
	virtual void DestructFunction() {};
	virtual void SpawnFrom(AActor* InTarget) {};
};

UCLASS()
class PROJECTA_API UPAPool : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UPAPool() override
	{
		ClearPool();
	}

	/** 초기화 (모든 ObjectType에 대한 공간 확보) */
	void InitPool(int32 InSize)
	{
		FactoryMap.Empty(InSize);
		ConstructorMap.Empty(InSize);
		DestructorMap.Empty(InSize);
	}

	/** 타입별 풀 초기화 */
	template<typename FactoryType, typename ConstructorType, typename DestructorType>
	void InitPool(EPoolingObjectType ObjectType, FactoryType&& FactoryFunc, ConstructorType&& ConstructorFunc, DestructorType&& DestructorFunc, int32 InitSize = 0)
	{
		FactoryMap.Emplace(ObjectType, Forward<FactoryType>(FactoryFunc));
		ConstructorMap.Emplace(ObjectType, Forward<ConstructorType>(ConstructorFunc));
		DestructorMap.Emplace(ObjectType, Forward<DestructorType>(DestructorFunc));

		if (InitSize > 0)
		{
			IncreasePool(ObjectType, InitSize);
		}
	}

	/** 풀 비우기 */
	void ClearPool()
	{
		ReferenceTable.Empty();
		ObjectPool.Empty();
		UsedObjectPool.Empty();
		FactoryMap.Empty();
		ConstructorMap.Empty();
		DestructorMap.Empty();
	}

	/** 오브젝트 요청 */
	UObject* GetObject(const EPoolingObjectType ObjectType, FPoolingUObjectHandle* OutHandle, bool bAllowExpand = true)
	{
		if (OutHandle == nullptr)
		{
			ensureMsgf(false, TEXT("OutHandle is null"));
			return nullptr;
		}

		TArray<UObject*> AvailableObjects;
		ObjectPool.MultiFind(ObjectType, AvailableObjects);

		if (AvailableObjects.IsEmpty() && bAllowExpand)
		{
			IncreasePool(ObjectType, 1);
			ObjectPool.MultiFind(ObjectType, AvailableObjects);
		}

		UObject* Selected = FindValidObjectFromPool(AvailableObjects);
		if (Selected == nullptr || Selected->IsValidLowLevel() == false)
		{
			return nullptr;
		}

		ObjectPool.RemoveSingle(ObjectType, Selected);

		if (TFunction<void(UObject*)>* Constructor = ConstructorMap.Find(ObjectType))
		{
			if(Constructor == nullptr)
			{
				check(false);
				return nullptr;
			}
			
			(*Constructor)(Selected);
		}

		FPoolingUObjectHandle Handle;
		Handle.Init(this, GenerateHandleIndex(), ObjectType, Selected);

		if (IPAPoolingUObject* Poolable = Cast<IPAPoolingUObject>(Selected))
		{
			Poolable->PoolingHandle = Handle;
		}

		UsedObjectPool.Add(Handle.Handle, Handle);
		*OutHandle = Handle;

		return Handle.Get();
	}

	/** 오브젝트 반환 */
	bool ReturnObject(FPoolingUObjectHandle* InOutHandle)
	{
		if (InOutHandle == nullptr || UsedObjectPool.Contains(InOutHandle->Handle) == false)
		{
			return false;
		}

		UObject* Object = InOutHandle->Get();
		if (Object == nullptr)
		{
			return false;
		}

		ResetObject(InOutHandle->Type(), Object);
		ObjectPool.Add(InOutHandle->Type(), Object);
		UsedObjectPool.Remove(InOutHandle->Handle);
		InOutHandle->Clear();

		return true;
	}

	/** 참조 테이블에 있는지 확인 */
	bool CheckReference(UObject* InObject) const
	{
		return ReferenceTable.Contains(InObject);
	}

protected:

	void IncreasePool(EPoolingObjectType ObjectType, int32 Count)
	{
		if (FactoryMap.Contains(ObjectType) == false)
		{
			ensureMsgf(false, TEXT("Factory not registered for type %d"), (int32)ObjectType);
			return;
		}

		TFunction<UObject*()>& Factory = FactoryMap[ObjectType];

		for (int32 i = 0; i < Count; ++i)
		{
			UObject* NewObject = Factory();
			if (NewObject == nullptr)
			{
				check(NewObject);
				continue;
			}

			ReferenceTable.Emplace(NewObject);
			ObjectPool.Add(ObjectType, NewObject);

			if (IPAPoolingUObject* Poolable = Cast<IPAPoolingUObject>(NewObject))
			{
				Poolable->IsManagedPool = true;
			}

			ResetObject(ObjectType, NewObject);
		}
	}

	virtual void ResetObject(EPoolingObjectType ObjectType, UObject* Object)
	{
		if (TFunction<void(UObject*)>* Destructor = DestructorMap.Find(ObjectType))
		{
			(*Destructor)(Object);
		}
	}

	UObject* FindValidObjectFromPool(const TArray<UObject*>& PoolList)
	{
		const int32 PoolSize = PoolList.Num() - 1;
		for (int32 i = PoolSize; i >= 0; --i)
		{
			if (IsValid(PoolList[i]))
			{
				return PoolList[i];
			}
		}
		return nullptr;
	}

	uint64 GenerateHandleIndex()
	{
		if (GenerateHandleSeed == TNumericLimits<uint64>::Max())
		{
			GenerateHandleSeed = 0;
		}
		return ++GenerateHandleSeed;
	}

private:
	UPROPERTY()
	TArray<UObject*> ReferenceTable;

	TMultiMap<EPoolingObjectType, UObject*> ObjectPool;
	TMap<uint64, FPoolingUObjectHandle> UsedObjectPool;

	TMap<EPoolingObjectType, TFunction<UObject*()>> FactoryMap;
	TMap<EPoolingObjectType, TFunction<void(UObject*)>> ConstructorMap;
	TMap<EPoolingObjectType, TFunction<void(UObject*)>> DestructorMap;

	uint64 GenerateHandleSeed = 0;
};