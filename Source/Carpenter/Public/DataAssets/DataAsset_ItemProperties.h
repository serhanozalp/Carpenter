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
	FORCEINLINE bool IsValid() const { return ItemData.Num() > 0 && Colors.Num() > 0; }

private:

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Data")
	TArray<FCarpenterItemData> ItemData;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Data")
	TArray<FColor> Colors;
	
};
