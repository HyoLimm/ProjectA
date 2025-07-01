// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PAGameInstance.generated.h"

class APAGameModeBase;
UCLASS()
class PROJECTA_API UPAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	static UPAGameInstance* GetGameInstance();



	TObjectPtr<APAGameModeBase> GetGameMode() const;
	
	virtual void Init() override;
protected:

	TObjectPtr<APAGameModeBase> CurrentGameMode;
};
