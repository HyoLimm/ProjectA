// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PAObjectPoolSubsystem.generated.h"

class UPAPool;
class APAPlayerBullet;

UCLASS()
class PROJECTA_API UPAObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	/** Called when world is ready to start gameplay before the game mode transitions to the correct state and call BeginPlay on all actors */
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UPAPool* GetPool() const;

	void CreatePool();
	void DestroyPool();
protected:
	template<typename T>
	T* SpawnActorFromClass(UObject* Outer, TSubclassOf<T> ClassToSpawn, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator)
	{
		if (IsValid(Outer) == false)
		{
			return nullptr;
		}

		UWorld* World = Outer->GetWorld();
		if (World == nullptr)
		{
			return nullptr;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		return World->SpawnActor<T>(ClassToSpawn, Location, Rotation, SpawnParams);
	}

	static UObject* FactoryPlayerBullet();
	static UObject* FactoryEnemyCharacter();
protected:
	UPROPERTY()
	TObjectPtr<UPAPool> Pool;

	UPROPERTY()
	TSubclassOf<APAPlayerBullet> BulletClass;
};
