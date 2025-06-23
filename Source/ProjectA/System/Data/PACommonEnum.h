// Copyright 2025 ProjectA All rights reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EPAWidgetType : uint8
{
	NONE = 0,
	Main_Widget,
};

UENUM(BlueprintType)
enum class EPAWidgetLayerType : uint8
{
	NONE = 0,
	MAIN_LAYER,
	POPUP_LAYER,
	TOAST_LAYER,
	SYSTEM_MESSAGE_LAYER,
};