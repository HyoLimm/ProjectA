// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PACommonEnum.h"
#include "Engine/DataAsset.h"
#include "PAUIDataAsset.generated.h"

class UPAUserWidget;

UCLASS()
class PROJECTA_API UPAUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPAWidgetType WidgetType = EPAWidgetType::NONE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EPAWidgetLayerType WidgetLayer = EPAWidgetLayerType::NONE;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AssetBundles = "UI"))
	TSoftClassPtr<UPAUserWidget> WidgetClass;
};
