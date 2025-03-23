// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CarpenterWidgetContract.h"

#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCarpenterWidgetContract::SetContractData(const FCarpenterContractData& ContractData)
{
	if (ItemMeshText && ItemColor)
	{
		ItemMeshText->SetText(FText::FromString(ContractData.RequestedItemData.Name));
		ItemColor->SetColorAndOpacity(ContractData.RequestedItemColor);
	}
}
