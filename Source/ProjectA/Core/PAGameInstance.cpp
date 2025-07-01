// Copyright 2025 ProjectA All rights reserved.


#include "PAGameInstance.h"

#include "PAGameModeBase.h"
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

TObjectPtr<APAGameModeBase> UPAGameInstance::GetGameMode() const
{
	if(GetWorld() == nullptr)
	{
		return nullptr;		
	}

	return GetWorld()->GetAuthGameMode<APAGameModeBase>();
}

void UPAGameInstance::Init()
{
	Super::Init();

	if(GetWorld())
	{
		GetWorld()->SetGameInstance(this);
	}
	
}

