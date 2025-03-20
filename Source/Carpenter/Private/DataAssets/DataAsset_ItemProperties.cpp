// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_ItemProperties.h"

FCarpenterItemData* UDataAsset_ItemProperties::GetRandomItemData()
{
	if (ItemData.IsEmpty())
	{
		return nullptr;
	}
	
	int32 RandomIndex = FMath::RandRange(0, ItemData.Num() - 1);
	return &ItemData[RandomIndex];
}

FColor* UDataAsset_ItemProperties::GetRandomColor()
{
	if (Colors.IsEmpty())
	{
		return nullptr;
	}
	int32 RandomIndex = FMath::RandRange(0, Colors.Num() - 1);
	return &Colors[RandomIndex];
}
