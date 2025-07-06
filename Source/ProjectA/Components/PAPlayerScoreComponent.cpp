// Copyright 2025 ProjectA All rights reserved.

#include "Components/PAPlayerScoreComponent.h"

UPAPlayerScoreComponent::UPAPlayerScoreComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
		CurrentScore(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPAPlayerScoreComponent::Init()
{
	Clear();
}

void UPAPlayerScoreComponent::Clear()
{
	CurrentScore = 0;
}

void UPAPlayerScoreComponent::AddScore(uint64 Score)
{
	CurrentScore +=Score;
	OnUpdateScore.Broadcast(CurrentScore);
}
