// Copyright 2025 ProjectA All rights reserved.


#include "PABaseBulletActor.h"

#include "Character/PAEnemyCharacter.h"
#include "Components/SphereComponent.h"


APABaseBulletActor::APABaseBulletActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent); 

	SphereComponent->SetSphereRadius(100.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Bullet"));
	SphereComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void APABaseBulletActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(SphereComponent))
	{
		SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBulletOverlap);
	}
}

// Called every frame
void APABaseBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void APABaseBulletActor::OnBulletOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
