// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PAActorComponent.h"
#include "PAHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPAHealth_DeathEvent, AActor*, OwningActor);

UENUM(BlueprintType)
enum class EPADeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS()
class PROJECTA_API UPAHealthComponent : public UPAActorComponent
{
	GENERATED_BODY()
public:
	UPAHealthComponent(const FObjectInitializer& ObjectInitializer);

	bool IsAlive() const { return DeathState == EPADeathState::NotDead; }
	
	virtual void StartDeath();
	virtual void FinishDeath();

	void SetMaxHealth(const float InHealth);
	
	void SetCurrenctHealth(const float InHealth);
	
	UFUNCTION(BlueprintCallable, Category = "PA|Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PA|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "PA|Health")
	float GetHealthNormalized() const;
	
public:
	UPROPERTY(BlueprintAssignable)
	FPAHealth_DeathEvent OnDeathStarted;

	UPROPERTY(BlueprintAssignable)
	FPAHealth_DeathEvent OnDeathFinished;

protected:

	float CurrentHealth = 0.f;
	float MaxHealth = 0.f;
	
	UPROPERTY()
	EPADeathState DeathState;
};
