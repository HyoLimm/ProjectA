// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "PALocalPlayerCharacter.generated.h"

class UPAWeaponSystemComponent;
class UPAPlayerScoreComponent;


UCLASS()
class PROJECTA_API APALocalPlayerCharacter : public APABaseCharacter
{
	GENERATED_BODY()
public:
	APALocalPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitCharacter() override;	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PA|PlayerCharacter", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPAWeaponSystemComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PA|PlayerCharacter", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPAPlayerScoreComponent> ScoreComponent;
	
	FTimerHandle BulletTimerHandle;

	bool bIsAutoAttack = true;

private:
	void OnFireBulletFromTimer();
};
