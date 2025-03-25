// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Shop/CarpenterWidgetContract.h"

#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCarpenterWidgetContract::SetContractData(const FCarpenterContractData& ContractData)
{
	ItemMeshText->SetText(FText::FromString(ContractData.RequestedItemData.Name));
	RewardAmountText->SetText(FText::AsNumber(ContractData.RewardAmount));
	ItemColor->SetColorAndOpacity(ContractData.RequestedItemColor);
}