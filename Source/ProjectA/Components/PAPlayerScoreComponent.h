// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PAPlayerScoreComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPAAddScoreEvent, uint64, Score);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UPAPlayerScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPAPlayerScoreComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "PA")
	static UPAPlayerScoreComponent* FindScoreComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UPAPlayerScoreComponent>() : nullptr); }
	
	void Init();
	void Clear();
	void AddScore(uint64 Score = 1);


	UPROPERTY(BlueprintAssignable)
	FPAAddScoreEvent OnUpdateScore;
	
protected:


	
	uint64 CurrentScore;
};
