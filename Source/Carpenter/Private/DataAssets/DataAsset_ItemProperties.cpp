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

FLinearColor* UDataAsset_ItemProperties::GetRandomColor()
{
	if (ColorList.IsEmpty())
	{
		return nullptr;
	}
	int32 RandomIndex = FMath::RandRange(0, ColorList.Num() - 1);
	return &ColorList[RandomIndex];
}

bool UDataAsset_ItemProperties::IsValid() const
{
	if (CarpenterItemDataList.Num() > 256)
	{
		UE_LOG(LogNetTraffic, Warning, TEXT("Using uint8 to replicate index. Carpenter Item Data List size should not exceed 256!"));
	}
	return CarpenterItemDataList.Num() > 0 && ColorList.Num() > 0;
}
