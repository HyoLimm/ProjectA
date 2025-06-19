// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PAGameModeBase.generated.h"

class UPAPool;
class APAEnemyCharacter;
class APAPlayerBullet;

UCLASS()
class PROJECTA_API APAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	APAGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void SpawnRandomEnemy();
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APAEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APAPlayerBullet> BulletClass;

protected:
	
	FTimerHandle EnemySpawnTimerHandle;


	TWeakObjectPtr<UPAPool> Pool;
};
