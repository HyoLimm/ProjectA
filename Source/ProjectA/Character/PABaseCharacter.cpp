// Fill out your copyright notice in the Description page of Project Settings.


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


void APABaseCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
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

