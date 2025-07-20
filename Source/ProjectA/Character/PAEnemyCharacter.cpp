// Copyright 2025 ProjectA All rights reserved.


#include "PAEnemyCharacter.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "Components/CapsuleComponent.h"
#include "Core/PAGameModeBase.h"
#include "Helpers/PACoreHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/AIController.h"

class UNavigationSystemV1;

APAEnemyCharacter::APAEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
}

void APAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APAEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsActive)
	{
		auto temp = GetController();
		auto temp2 = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
		if (temp && temp2)
		{
			// MoveToActor로 계속 추적
			AAIController* AIController = Cast<AAIController>(GetController());
			AIController->MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(),0), 100.f, true, true, true, nullptr, true);

		}
	}
	
}

void APAEnemyCharacter::ConstructFunction()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void APAEnemyCharacter::DestructFunction()
{	
	SetActorHiddenInGame(true);
	bIsActive = false;
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
}

void APAEnemyCharacter::SpawnFrom(AActor* InTarget)
{
	if (bIsActive)
	{
		return;
	}


	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	const FVector& PlayerLocation = PlayerPawn->GetActorLocation();


	// 2D 랜덤 방향 벡터
	const float Angle = FMath::FRandRange(0.f, 2.f * PI);
	const float Distance = FMath::FRandRange(0.f, 1000.f);

	const float OffsetX = FMath::Cos(Angle) * Distance;
	const float OffsetY = FMath::Sin(Angle) * Distance;

	const FVector& RandomLocation = PlayerLocation + FVector(OffsetX, OffsetY, 0.f);

	SetActorLocation(RandomLocation);

	bIsActive = true;
}

void APAEnemyCharacter::StartDead()
{
	TWeakObjectPtr<UPAPool> Pool =  PA::Core::GetObjectPool();	
	if(Pool.IsValid())
	{
		Pool.Get()->ReturnObject(this->GetPoolingHandle());	
	}

	bIsActive = false;
}

void APAEnemyCharacter::FinishDead()
{
}
