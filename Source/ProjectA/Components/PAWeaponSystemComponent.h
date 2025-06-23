// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PAActorComponent.h"
#include "PAWeaponSystemComponent.generated.h"

class UPAPool;
class APAPlayerBullet;


UCLASS()
class PROJECTA_API UPAWeaponSystemComponent : public UPAActorComponent
{
	GENERATED_BODY()
public:
	virtual void Activate(bool bReset) override;

	void FireBullet();

	UFUNCTION(BlueprintPure, Category = "PA|Waepon")
	static UPAWeaponSystemComponent* FindWeaponSystemComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UPAWeaponSystemComponent>() : nullptr); }

protected:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APAPlayerBullet> BulletClass;


	bool bIsFirebullet = false;
};
