// Copyright 2025 ProjectA All rights reserved.


#include "Core/Subsystem/PAUIManagerSubsystem.h"

#include "Core/PAGameInstance.h"
#include "Core/PAGameModeBase.h"
#include "System/PAAssetManager.h"
#include "System/Data/PAUIDataAsset.h"

void UPAUIManagerSubsystem::LoadAssetStart()
{
	UPAAssetManager& AssetManager = UPAAssetManager::Get();
	
	
	// PrimaryAsset 기반으로 로드할 자산 목록 (번들)
	TSet<FPrimaryAssetId> BundleAssetList;
	
	// SoftObjectPath 기반의 자산 목록 (경로 기반)
	TSet<FSoftObjectPath> RawAssetList;
	FString Temp;
	UPAGameInstance* GameInstance = Cast<UPAGameInstance>(GetGameInstance());
	if(IsValid(GameInstance))
	{
		TWeakObjectPtr<APAGameModeBase> Temp22 = GetWorld()->GetAuthGameMode<APAGameModeBase>();
		TWeakObjectPtr<APAGameModeBase> GameMode = GameInstance->GetGameMode();
		if(GameMode.IsValid())
		{
			BundleAssetList.Add(GameMode->MainWidgetDataAsset->GetPrimaryAssetId());
			Temp = GameMode->MainWidgetDataAsset->GetPrimaryAssetId().ToString();
		}
	}


	//어디선가 등록해야됨....
	
	//BundleAssetList.Add(FPABundles::UI);
	
	// 실제 로딩할 번들 이름 지정
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(UPAAssetManager::UI);
	
	// Bundle 기반 자산 로딩 요청
	TSharedPtr<FStreamableHandle> BundleLoadHandle = nullptr;
	if (BundleAssetList.Num() > 0)
	{
		BundleLoadHandle = AssetManager.ChangeBundleStateForPrimaryAssets(BundleAssetList.Array(), BundlesToLoad, {}, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);
	}
	
	// Raw 경로 기반 자산 로딩 (지금은 비어있음)
	TSharedPtr<FStreamableHandle> RawLoadHandle = nullptr;
	if (RawAssetList.Num() > 0)
	{
		//안탈듯?
		RawLoadHandle = AssetManager.LoadAssetList(RawAssetList.Array(), FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority, TEXT("StartAssetLoad()"));
	}
	
	// 두 로딩 핸들을 병합
	TSharedPtr<FStreamableHandle> Handle = nullptr;
	if (BundleLoadHandle.IsValid() && RawLoadHandle.IsValid())
	{
		// 둘 다 있으면 병합 핸들 생성
		Handle = AssetManager.GetStreamableManager().CreateCombinedHandle({ BundleLoadHandle, RawLoadHandle });
	}
	else
	{
		// 둘 중 하나만 존재하면 그대로 사용
		Handle = BundleLoadHandle.IsValid() ? BundleLoadHandle : RawLoadHandle;
	}
	
	
	// 로딩 완료 시 실행될 Delegate (준비 완료 처리)
	FStreamableDelegate OnAssetsLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadComplete);
	
	// 이미 자산이 로드되었으면 즉시 콜백 실행
	if (Handle.IsValid() == false || Handle->HasLoadCompleted())
	{
		FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
	}
	else
	{
		// 비동기 로딩 완료 후 콜백 바인딩
		Handle->BindCompleteDelegate(OnAssetsLoadedDelegate);
	
		// 로딩 취소되더라도 콜백이 호출되도록 안전 처리
		Handle->BindCancelDelegate(FStreamableDelegate::CreateLambda([OnAssetsLoadedDelegate]()
		{
			OnAssetsLoadedDelegate.ExecuteIfBound();
		}));
	}
}

void UPAUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UPAUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPAUIManagerSubsystem::ShowMainWidget()
{
}

void UPAUIManagerSubsystem::OnLoadComplete()
{
}
