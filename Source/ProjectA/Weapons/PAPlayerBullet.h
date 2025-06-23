// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/PAPool.h"
#include "Weapons/PABaseBulletActor.h"
#include "PAPlayerBullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APAPlayerBullet : public APABaseBulletActor, public IPAPoolingUObject
{
	GENERATED_BODY()
		
public:	
	APAPlayerBullet(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	virtual void SpawnFrom(AActor* InTarget) override;

	void Fire();

	virtual void NotifyActorBeginOverlap(class AActor* Other) override;
	
public:
	virtual void ConstructFunction() override;
	virtual void DestructFunction() override;
protected:	
	virtual void OnBulletOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
protected:
	FVector2d CurrentLocation;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<AActor> OwnerCharacter;
	
	inline static FVector2D WorldCenter = FVector2d::ZeroVector;
	inline static float MaxDistance = 2000.f;
};
