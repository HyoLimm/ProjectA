// Copyright 2025 ProjectA All rights reserved.


#include "Development/PADeveloperSettings.h"

UPADeveloperSettings::UPADeveloperSettings()
{
}

FName UPADeveloperSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
