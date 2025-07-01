// Copyright 2025 ProjectA All rights reserved.


#include "PAUIDataAsset.h"

#include "System/PAAssetManager.h"
#if WITH_EDITOR
EDataValidationResult UPAUIDataAsset::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);
	return Result;
}
#endif

#if WITH_EDITORONLY_DATA
void UPAUIDataAsset::UpdateAssetBundleData()
{
	Super::UpdateAssetBundleData();
	
	AssetBundleData.AddBundleAsset(UPAAssetManager::UI,WidgetClass.ToSoftObjectPath().GetAssetPath());
}
#endif // WITH_EDITORONLY_DATA