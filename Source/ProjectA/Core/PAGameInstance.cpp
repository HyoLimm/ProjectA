// Copyright 2025 ProjectA All rights reserved.


#include "PAGameInstance.h"

#include "Kismet/GameplayStatics.h"

UPAGameInstance* UPAGameInstance::GetGameInstance()
{
	if ( GWorld == nullptr)
	{
		check(GWorld);
		return nullptr;
	}

	return Cast<UPAGameInstance>(GWorld->GetGameInstance());
}

void UPAGameInstance::SetGameMode(APAGameModeBase* InGameMode)
{
	CurrentGameMode = InGameMode;
}

TObjectPtr<APAGameModeBase> UPAGameInstance::GetGameMode() const
{
	return CurrentGameMode;
}

void UPAGameInstance::Init()
{
	Super::Init();

	if(GetWorld())
	{
		GetWorld()->SetGameInstance(this);
	}
}

