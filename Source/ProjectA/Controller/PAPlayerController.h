// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidgetPool.h"
#include "GameFramework/PlayerController.h"
#include "PAPlayerController.generated.h"

class UPAUserWidget;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PROJECTA_API APAPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APAPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;
protected:
	bool bIsAttachedMainWidget = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPAUserWidget> MainWidgetClass;

	UPROPERTY(Transient)
	FUserWidgetPool GeneratedWidgetsPool;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};

