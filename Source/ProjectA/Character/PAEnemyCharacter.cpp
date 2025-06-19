// Fill out your copyright notice in the Description page of Project Settings.


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
	if(bIsActive)
	{
		return;
	}

	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}

	const FVector& PlayerLocation = PlayerPawn->GetActorLocation();

	// 네비게이션 시스템 사용해서 안전한 위치 찾기
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSystem) return;

	FNavLocation RandomLocation;
	bool bFound = NavSystem->GetRandomReachablePointInRadius(PlayerLocation, 1000.f, RandomLocation);

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
