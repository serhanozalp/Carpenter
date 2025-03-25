// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CarpenterWidgetContract.generated.h"

struct FCarpenterContractData;
class UImage;
class UTextBlock;

UCLASS()
class CARPENTER_API UCarpenterWidgetContract : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetContractData(const FCarpenterContractData& ContractData);

private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemMeshText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemColor;
};
