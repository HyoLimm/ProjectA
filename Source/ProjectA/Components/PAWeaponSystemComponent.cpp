// Copyright 2025 ProjectA All rights reserved.


#include "PAWeaponSystemComponent.h"

#include "Core/PAGameInstance.h"
#include "Core/PAPool.h"
#include "Helpers/PACoreHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/PAPlayerBullet.h"

void UPAWeaponSystemComponent::Activate(bool bReset)
{
	Super::Activate(bReset);	
}

void UPAWeaponSystemComponent::FireBullet()
{	
	TWeakObjectPtr<UPAPool> Pool =  PA::Core::GetObjectPool();	
	if (Pool.IsValid() == false)
	{
		return;
	}

	FPoolingUObjectHandle Handle;
	UObject* BulletObj = Pool.Get()->GetObject(EPoolingObjectType::PLAYER_BULLET, &Handle);
	if (BulletObj)
	{
		APAPlayerBullet* Bullet = Cast<APAPlayerBullet>(BulletObj);
		if (Bullet)
		{
			Bullet->SpawnFrom(GetOwner());
			Bullet->Fire();
		}
	}
}
