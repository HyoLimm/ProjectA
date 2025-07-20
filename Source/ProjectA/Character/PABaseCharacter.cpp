// Copyright 2025 ProjectA All rights reserved.


#include "PABaseCharacter.h"

#include "ProjectA/Components/PAHealthComponent.h"


APABaseCharacter::APABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UPAHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);
}

void APABaseCharacter::InitCharacter()
{
}


void APABaseCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void APABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APABaseCharacter::OnDeathStarted(AActor* OwningActor)
{
}

void APABaseCharacter::OnDeathFinished(AActor* OwningActor)
{
}

