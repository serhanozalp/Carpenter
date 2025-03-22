// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_ItemProperties.h"

FCarpenterItemData* UDataAsset_ItemProperties::GetRandomItemData()
{
	if (CarpenterItemDataList.IsEmpty())
	{
		return nullptr;
	}
	
	int32 RandomIndex = FMath::RandRange(0, CarpenterItemDataList.Num() - 1);
	return &CarpenterItemDataList[RandomIndex];
}

FColor* UDataAsset_ItemProperties::GetRandomColor()
{
	if (ColorList.IsEmpty())
	{
		return nullptr;
	}
	int32 RandomIndex = FMath::RandRange(0, ColorList.Num() - 1);
	return &ColorList[RandomIndex];
}
