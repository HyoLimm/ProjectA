// Copyright 2025 ProjectA All rights reserved.


#include "PAHealthComponent.h"

UPAHealthComponent::UPAHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
	DeathState = EPADeathState::NotDead;
	CurrentHealth = 0.0f;
	MaxHealth = 0.0f;
}

void UPAHealthComponent::StartDeath()
{
	if (DeathState != EPADeathState::NotDead)
	{
		return;
	}

	DeathState = EPADeathState::DeathStarted;
	
	AActor* Owner = GetOwner();
	
	check(Owner);

	OnDeathStarted.Broadcast(Owner);
}

void UPAHealthComponent::FinishDeath()
{
	if (DeathState != EPADeathState::DeathStarted)
	{
		return;
	}

	DeathState = EPADeathState::DeathFinished;

	AActor* Owner = GetOwner();
	check(Owner);
	
	OnDeathFinished.Broadcast(Owner);
}

void UPAHealthComponent::SetMaxHealth(const float InHealth)
{
	MaxHealth = InHealth;
}

void UPAHealthComponent::SetCurrenctHealth(const float InHealth)
{
	CurrentHealth = InHealth;
}

float UPAHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UPAHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UPAHealthComponent::GetHealthNormalized() const
{
	return ((MaxHealth > 0.0f) ? (CurrentHealth / MaxHealth) : 0.0f);
}
