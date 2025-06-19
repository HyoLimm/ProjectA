// Copyright 2025 ProjectA All rights reserved.


#include "PACoreHelper.h"

#include "Core/PAGameInstance.h"

UPAObjectPoolSubsystem* PA::Core::GetObjectPoolSubsystem(const UObject* WorldContext)
{	
	return Cast<UWorld>(WorldContext)->GetSubsystem<UPAObjectPoolSubsystem>();
}

UPAPool* PA::Core::GetObjectPool()
{
	UPAGameInstance* GameInstance = UPAGameInstance::GetGameInstance();
	check(GameInstance);
	if (IsValid(GameInstance) == false)
	{
		return nullptr;
	}

	UWorld* World = GameInstance->GetWorld();
	check(World);
	if (IsValid(World) == false)
	{
		return nullptr;
	}
	
	TWeakObjectPtr<UPAObjectPoolSubsystem> ObjectPoolSubsystem = World->GetSubsystem<UPAObjectPoolSubsystem>();
	if (ObjectPoolSubsystem.IsValid() == false)
	{
		return nullptr;
	}

	return ObjectPoolSubsystem.Get()->GetPool();
}
