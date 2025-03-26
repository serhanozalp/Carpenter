// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Engine/DataAsset.h"
#include "DataAsset_ItemProperties.generated.h"

UCLASS()
class CARPENTER_API UDataAsset_ItemProperties : public UDataAsset
{
	GENERATED_BODY()

public:

	//PROPERTY

	UPROPERTY(EditDefaultsOnly, Category = "Custom|DataAsset_ItemProperties|Data")
	TArray<FCarpenterItemData> CarpenterItemDataList;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|DataAsset_ItemProperties|Data")
	TArray<FLinearColor> ColorList;
	
	//METHOD
	
	FCarpenterItemData* GetRandomItemData();
	FLinearColor* GetRandomColor();
	
	bool IsValid() const;
};
