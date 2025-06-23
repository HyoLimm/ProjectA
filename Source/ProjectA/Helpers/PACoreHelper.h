// Copyright 2025 ProjectA All rights reserved.

#pragma once
#include "Core/PAObjectPoolSubsystem.h"

namespace PA
{
	namespace Core
	{
		UPAObjectPoolSubsystem* GetObjectPoolSubsystem(const UObject* WorldContext);		
		UPAPool* GetObjectPool();		
	}
}
