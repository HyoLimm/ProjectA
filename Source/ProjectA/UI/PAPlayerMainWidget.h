// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget/PABaseMainWidget.h"
#include "PAPlayerMainWidget.generated.h"

class UTextBlock;


UCLASS()
class PROJECTA_API UPAPlayerMainWidget : public UPABaseMainWidget
{
	GENERATED_BODY()
protected:
	UPAPlayerMainWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TT_CurrentScore;
};
