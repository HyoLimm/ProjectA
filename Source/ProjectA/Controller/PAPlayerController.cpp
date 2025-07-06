// Copyright 2025 ProjectA All rights reserved.


#include "Controller/PAPlayerController.h"

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
