// Copyright 2025 ProjectA All rights reserved.


#include "Controller/PAPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SOverlay.h"
#include "UI/BaseWidget/PAUserWidget.h"

APAPlayerController::APAPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

{
}

void APAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerInputMappingContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerInputMappingContext, 0);
	
	
	GeneratedWidgetsPool.SetWorld(GetWorld());

	if (bIsAttachedMainWidget == false && MainWidgetClass)
	{
		UPAUserWidget* MainWidget = GeneratedWidgetsPool.GetOrCreateInstance(MainWidgetClass);
		if (IsValid(MainWidget))
		{
			MainWidget->AddToViewport();
			bIsAttachedMainWidget = true;
		}
	}
}

void APAPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GeneratedWidgetsPool.ReleaseAll();
	
	Super::EndPlay(EndPlayReason);	
}

void APAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APAPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void APAPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void APAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void APAPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D& InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator& Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisValue.X);
	}
}
