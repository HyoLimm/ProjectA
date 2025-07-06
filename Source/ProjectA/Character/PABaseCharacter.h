// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PABaseCharacter.generated.h"

class UPAHealthComponent;

UCLASS()
class PROJECTA_API APABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APABaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PA|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPAHealthComponent> HealthComponent;

protected:
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	
};
