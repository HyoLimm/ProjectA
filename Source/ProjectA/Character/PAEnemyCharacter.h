// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "Core/PAPool.h"
#include "PAEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APAEnemyCharacter : public APABaseCharacter, public IPAPoolingUObject
{
	GENERATED_BODY()
	
public:
	APAEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void ConstructFunction() override;
	virtual void DestructFunction() override;
	virtual void SpawnFrom(AActor* InTarget) override;


	void StartDead();
	void FinishDead();
	
	bool bIsActive = false;

	
};
