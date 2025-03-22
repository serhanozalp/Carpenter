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

	FCarpenterItemData* GetRandomItemData();
	FColor* GetRandomColor();
	FORCEINLINE bool IsValid() const { return CarpenterItemDataList.Num() > 0 && ColorList.Num() > 0; }

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Data")
	TArray<FCarpenterItemData> CarpenterItemDataList;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Data")
	TArray<FColor> ColorList;
};
