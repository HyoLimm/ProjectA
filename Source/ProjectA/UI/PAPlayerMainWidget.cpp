// Copyright 2025 ProjectA All rights reserved.


#include "UI/PAPlayerMainWidget.h"

#include "Character/PALocalPlayerCharacter.h"
#include "Components/PAPlayerScoreComponent.h"
#include "Components/TextBlock.h"
#include "Controller/PAPlayerController.h"
#include "Core/PAGameInstance.h"

UPAPlayerMainWidget::UPAPlayerMainWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)	 
{
}

void UPAPlayerMainWidget::NativeConstruct()
{
	Super::NativeConstruct();


	TWeakObjectPtr<APAPlayerController> PlayerController = Cast<APAPlayerController>(UPAGameInstance::GetGameInstance()->GetFirstLocalPlayerController(GetWorld()));
	if(PlayerController.IsValid())
	{
		PlayerController.Get()->OnPossessedPawnChanged.AddDynamic(this,&ThisClass::OnPossessedPawnChanged);
		OnPossessedPawnChanged(nullptr,PlayerController.Get()->GetPawn());
	}
	
}

void UPAPlayerMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPAPlayerMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPAPlayerMainWidget::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if(IsValid(NewPawn))
	{
		APALocalPlayerCharacter* OwnerCharacter = Cast<APALocalPlayerCharacter>(NewPawn);
		if(IsValid(OwnerCharacter))
		{
			UPAPlayerScoreComponent* ScoreComponent = UPAPlayerScoreComponent::FindScoreComponent(OwnerCharacter);
			if(IsValid(ScoreComponent))
			{
				ScoreComponent->OnUpdateScore.RemoveDynamic(this,&ThisClass::OnUpdateScore);	
				ScoreComponent->OnUpdateScore.AddDynamic(this,&ThisClass::OnUpdateScore);	
			}	
		}
	}
}

void UPAPlayerMainWidget::OnUpdateScore(uint64 InUpdateScore)
{
	if (IsValid(TT_CurrentScore))
	{
		TT_CurrentScore->SetText(FText::AsNumber(InUpdateScore));
	}
}
