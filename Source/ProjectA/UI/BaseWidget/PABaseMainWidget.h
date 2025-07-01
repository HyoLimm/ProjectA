// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget/PAUserWidget.h"
#include "PABaseMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPABaseMainWidget : public UPAUserWidget
{
	GENERATED_BODY()
public :
	UPABaseMainWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
