// Fill out your copyright notice in the Description page of Project Settings.


#include "PALocalPlayerCharacter.h"

#include "Components/PAWeaponSystemComponent.h"

APALocalPlayerCharacter::APALocalPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponComponent = CreateDefaultSubobject<UPAWeaponSystemComponent>(TEXT("WeaponComponent"));

}

void APALocalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponComponent && bIsAutoAttack)
	{
		if(GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(BulletTimerHandle, this, &ThisClass::OnFireBulletFromTimer,0.3f, true);
		}
	}
}

void APALocalPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APALocalPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APALocalPlayerCharacter::OnFireBulletFromTimer()
{
	if(WeaponComponent && WeaponComponent->IsActive())
	{
		WeaponComponent->FireBullet();
	}
}
