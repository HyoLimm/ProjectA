// Copyright 2025 ProjectA All rights reserved.


#include "System/PAAssetManager.h"
#include "PALogChannels.h"


static FAutoConsoleCommand CVarDumpLoadedAssets(
	TEXT("PA.DumpLoadedAssets"),
	TEXT(" Asset Manager를 통해 로드되어 현재 메모리에 존재하는 모든 애셋 표시."),
	FConsoleCommandDelegate::CreateStatic(UPAAssetManager::DumpLoadedAssets)
);

const FName UPAAssetManager::UI(TEXT("UI"));


UPAAssetManager& UPAAssetManager::Get()
{
	check(GEngine);

	if (UPAAssetManager* Singleton = Cast<UPAAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogPA, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to PAAssetManager!"));

	// Fatal error above prevents this from being called.
	return *NewObject<UPAAssetManager>();
}

void UPAAssetManager::DumpLoadedAssets()
{
	UE_LOG(LogPA, Log, TEXT("========== Start Dumping Loaded Assets =========="));

	for (const UObject* LoadedAsset : Get().LoadedAssets)
	{
		UE_LOG(LogPA, Log, TEXT("  %s"), *GetNameSafe(LoadedAsset));
	}

	UE_LOG(LogPA, Log, TEXT("... %d assets in loaded pool"), Get().LoadedAssets.Num());
	UE_LOG(LogPA, Log, TEXT("========== Finish Dumping Loaded Assets =========="));
}

UObject* UPAAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		if (ShouldLogAssetLoads())
		{
			//애셋 로딩 시간 측정 로그를 찍는 코드
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// Asset Manager가 아직 준비되지 않았다면 LoadObject를 사용.
		return AssetPath.TryLoad();
	}

	return nullptr;
}

bool UPAAssetManager::ShouldLogAssetLoads()
{
	static bool bLogAssetLoads = FParse::Param(FCommandLine::Get(), TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

void UPAAssetManager::AddLoadedAsset(const UObject* InAsset)
{
	if (ensureAlways(InAsset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(InAsset);
	}
}
