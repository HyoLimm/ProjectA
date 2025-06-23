// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PABaseBulletActor.generated.h"

class USphereComponent;

USTRUCT(BlueprintType)
struct FBulletInfo
{
	GENERATED_BODY()
public:
	FBulletInfo()
		: StartPosition(FVector2D::ZeroVector),Direction(FVector2D::ZeroVector),Speed(0.0f)
	{}
	~FBulletInfo() = default;
	void Clear()
	{
		StartPosition = FVector2D::ZeroVector;
		Direction = FVector2D::ZeroVector;
		Speed = 1500.f; 
	}
	
	FVector2D StartPosition = FVector2D::ZeroVector;
	FVector2D Direction = FVector2D::ZeroVector;
	float Speed = 1500.f; // 유닛당 초속
};

UCLASS()
class PROJECTA_API APABaseBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APABaseBulletActor(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION()
	virtual void OnBulletOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	
	
	FBulletInfo BulletInfo;	
	
	bool bIsActive = false;
};
