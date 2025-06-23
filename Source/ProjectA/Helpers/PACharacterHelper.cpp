// Copyright 2025 ProjectA All rights reserved.


#include "PACharacterHelper.h"

FVector2D PA::CharacterHelper::GetActorLocation2D(const AActor* InTarget)
{
	if(InTarget == nullptr)
	{
		return FVector2D::ZeroVector;
	}	
	const FVector& Location3D = InTarget->GetActorLocation();
	
	FVector2D Location2D(Location3D.X, Location3D.Y);
	return Location2D;
}

FVector2D PA::CharacterHelper::GetActorForward2D(const AActor* InTarget)
{
	if(InTarget == nullptr)
	{
		return FVector2D::ZeroVector;
	}	
	const FVector& Location3D = InTarget->GetActorForwardVector();
	
	FVector2D Location2D(Location3D.X, Location3D.Y);
	return Location2D;
}
