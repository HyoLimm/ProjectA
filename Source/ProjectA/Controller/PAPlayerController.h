// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APAPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
};
