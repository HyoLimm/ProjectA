// Copyright 2025 ProjectA All rights reserved.


#include "Core/PAObjectPoolSubsystem.h"

#include "PAGameInstance.h"
#include "PAGameModeBase.h"
#include "PAPool.h"
#include "Character/PAEnemyCharacter.h"
#include "Weapons/PAPlayerBullet.h"

void UPAObjectPoolSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

UPAPool* UPAObjectPoolSubsystem::GetPool() const
{
	return Pool;
}

void UPAObjectPoolSubsystem::CreatePool()
{
	if(Pool)
	{
		return;
	}
	Pool = NewObject<UPAPool>(this); 
	check(Pool);
	
	TFunction<UObject*()> FactoryFunc = [this]()
	{
		return SpawnActorFromClass<APAPlayerBullet>(this, BulletClass);
	};	
	
	Pool->InitPool(EPoolingObjectType::PLAYER_BULLET,&UPAObjectPoolSubsystem::FactoryPlayerBullet,[](UObject* Obj) { Cast<APAPlayerBullet>(Obj)->ConstructFunction(); },[](UObject* Obj) { Cast<APAPlayerBullet>(Obj)->DestructFunction(); },30);
	Pool->InitPool(EPoolingObjectType::ENEMY,&UPAObjectPoolSubsystem::FactoryEnemyCharacter,[](UObject* Obj) { Cast<APAEnemyCharacter>(Obj)->ConstructFunction(); },[](UObject* Obj) { Cast<APAEnemyCharacter>(Obj)->DestructFunction(); },30);
}

void UPAObjectPoolSubsystem::DestroyPool()
{
}

UObject* UPAObjectPoolSubsystem::FactoryPlayerBullet()
{
	TWeakObjectPtr<UPAGameInstance> GameInstance = UPAGameInstance::GetGameInstance();
	if(GameInstance.IsValid() == false)
	{
		return nullptr;
	}
	
	UWorld* World = GameInstance.Get()->GetWorld();
	if (World == nullptr)
	{
		return nullptr;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TWeakObjectPtr<APAGameModeBase> GameMode = GameInstance.Get()->GetGameMode();
	if (GameMode.IsValid() && IsValid(GameMode->BulletClass))
	{
		return World->SpawnActor<APAPlayerBullet>(GameMode.Get()->BulletClass, FVector3d::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}		
	
	
	return nullptr;
}

UObject* UPAObjectPoolSubsystem::FactoryEnemyCharacter()
{
	TWeakObjectPtr<UPAGameInstance> GameInstance = UPAGameInstance::GetGameInstance();
	if(GameInstance.IsValid() == false)
	{
		return nullptr;
	}
	
	UWorld* World = GameInstance.Get()->GetWorld();
	if (World == nullptr)
	{
		return nullptr;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TWeakObjectPtr<APAGameModeBase> GameMode = GameInstance.Get()->GetGameMode();
	if (GameMode.IsValid() && IsValid(GameMode->EnemyClass))
	{
		return World->SpawnActor<APAEnemyCharacter>(GameMode.Get()->EnemyClass, FVector3d::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}		
	
	
	return nullptr;
}
