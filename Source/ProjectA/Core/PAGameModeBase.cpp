// Copyright 2025 ProjectA All rights reserved.


#include "PAGameModeBase.h"

#include "PAGameInstance.h"
#include "PAHUD.h"
#include "PAObjectPoolSubsystem.h"
#include "PAPool.h"
#include "Character/PAEnemyCharacter.h"
#include "Controller/PAPlayerController.h"
#include "Subsystem/PAUIManagerSubsystem.h"
#include "Weapons/PAPlayerBullet.h"

class UPAObjectPoolSubsystem;

APAGameModeBase::APAGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = APABaseCharacter::StaticClass();
	PlayerControllerClass = APAPlayerController::StaticClass();
	HUDClass = APAHUD::StaticClass();
}

void APAGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void APAGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UPAGameInstance* GameInstance = UPAGameInstance::GetGameInstance();
	if (IsValid(GameInstance) == false)
	{
		return;
	}

	UWorld* World = GameInstance->GetWorld();
	if(World)
	{
		TWeakObjectPtr<UPAObjectPoolSubsystem> ObjectPoolSubsystem = World->GetSubsystem<UPAObjectPoolSubsystem>();
		if (ObjectPoolSubsystem.IsValid())
		{
			ObjectPoolSubsystem.Get()->CreatePool();
			Pool = ObjectPoolSubsystem.Get()->GetPool();
		}
	}

	if(World)
	{
		World->GetTimerManager().SetTimer(EnemySpawnTimerHandle, this, &ThisClass::SpawnRandomEnemy,0.5f, true);
	}
	
	
	UPAUIManagerSubsystem* UIManagerSubSystem = GameInstance->GetSubsystem<UPAUIManagerSubsystem>();
	if(IsValid(UIManagerSubSystem))
	{
		UIManagerSubSystem->LoadAssetStart();
	}
}

void APAGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void APAGameModeBase::SpawnRandomEnemy()
{	
	if(Pool.IsValid() == false)
	{
		return;
	}
	
	FPoolingUObjectHandle Handle;
	UObject* SpawnedEnemy = Pool->GetObject(EPoolingObjectType::ENEMY,&Handle);
	if(SpawnedEnemy)
	{
		APAEnemyCharacter* TargetEnemy = Cast<APAEnemyCharacter>(SpawnedEnemy);
		if(TargetEnemy)
		{
			TargetEnemy->SpawnFrom(this);
		}
	}
	
}
