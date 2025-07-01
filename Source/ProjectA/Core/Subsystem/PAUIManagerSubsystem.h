// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PAUIManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void LoadAssetStart();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void ShowMainWidget();

private:
	void OnLoadComplete();
};
