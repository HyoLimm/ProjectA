// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PAAssetManager.generated.h"
#define UE_API PROJECTA_API


struct FPABundles
{
	inline static const FName UI = ("UI");
};

UCLASS(MinimalAPI, Config = Game)
class UPAAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UPAAssetManager& Get();
	
	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	static UE_API void DumpLoadedAssets();

protected:
	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
	static bool ShouldLogAssetLoads();

	//메모리에 유지하기 위해 로드된 자산을 추가하는 스레드 안전한 방법
	void AddLoadedAsset(const UObject* Asset);

private:
	//Asset Manager에 의해 로드되고 추적되는 애셋들
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;
	
	// 로드된 애셋 목록을 수정할 때 사용하는 스코프 잠금(lock)
	FCriticalSection LoadedAssetsCritical;
};

template <typename AssetType>
AssetType* UPAAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	do
	{
		const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
		if (false == AssetPath.IsValid())
		{
			break;
		}

		AssetType* LoadedAsset = AssetPointer.Get();
		if (nullptr == LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			// Added to loaded asset list.
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}

		return LoadedAsset;

	} while (false);

	return nullptr;
}
