// Copyright 2025 ProjectA All rights reserved.


#include "Weapons/PAPlayerBullet.h"

#include "Character/PAEnemyCharacter.h"
#include "Components/PAWeaponSystemComponent.h"
#include "Core/PAObjectPoolSubsystem.h"
#include "Helpers/PACharacterHelper.h"
#include "Helpers/PACoreHelper.h"

APAPlayerBullet::APAPlayerBullet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APAPlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsActive)
	{
		CurrentLocation += BulletInfo.Direction * BulletInfo.Speed * DeltaTime;

		if (OwnerCharacter.IsValid())
		{
			const FVector NewWorldPosition(CurrentLocation.X, CurrentLocation.Y, OwnerCharacter.Get()->GetActorLocation().Z);
			SetActorLocation(NewWorldPosition);
		
			FVector2D BulletLocation2D = PA::CharacterHelper::GetActorLocation2D(this);
			FVector2D OwnerLocation2D = PA::CharacterHelper::GetActorLocation2D(OwnerCharacter.Get());

			if (FVector2D::Distance(BulletLocation2D, OwnerLocation2D) > MaxDistance)
			{
				UPAObjectPoolSubsystem* ObjSubsystem = PA::Core::GetObjectPoolSubsystem(GetWorld());
				if(IsValid(ObjSubsystem))
				{
					TWeakObjectPtr<UPAPool> Pool = ObjSubsystem->GetPool();
					if(Pool.IsValid())
					{
						Pool.Get()->ReturnObject(this->GetPoolingHandle());	
					}
				}
				
			}
		}
	}
}

void APAPlayerBullet::SpawnFrom(AActor* InTarget)
{
	OwnerCharacter = InTarget;
}

void APAPlayerBullet::Fire()
{
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	if (bIsActive)
	{
		return;
	}

	BulletInfo.StartPosition = PA::CharacterHelper::GetActorLocation2D(OwnerCharacter.Get());
	BulletInfo.Direction = PA::CharacterHelper::GetActorForward2D(OwnerCharacter.Get());
	BulletInfo.Speed = 1500.f;
	
	CurrentLocation = BulletInfo.StartPosition;
	
	bIsActive = true;
	SetActorTickEnabled(true);
}

void APAPlayerBullet::NotifyActorBeginOverlap(class AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);

	APAEnemyCharacter* Target = Cast<APAEnemyCharacter>(Other);
	if(Target != nullptr)
	{
		
	}
}

void APAPlayerBullet::ConstructFunction()
{
	BulletInfo.Clear();
	SetActorHiddenInGame(false);
}

void APAPlayerBullet::DestructFunction()
{
	bIsActive = false;
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
}

void APAPlayerBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBulletOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(IsValid(OtherActor))
	{
		auto Target = Cast<APAEnemyCharacter>(MakeWeakObjectPtr(OtherActor));
		if(IsValid(Target))
		{
			Target->StartDead();
		}
	}
}
