// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CarpenterWidgetContractsHolder.h"

#include "Carpenter/DebugHelper.h"
#include "Components/ContractSystemComponent.h"
#include "Components/HorizontalBox.h"
#include "Widgets/CarpenterWidgetContract.h"

void UCarpenterWidgetContractsHolder::SetupOnContractListChangedDelegate(UContractSystemComponent* ContractSystemComponent)
{
	if (ContractSystemComponent)
	{
		ContractSystemComponent->OnContractListChanged.AddUObject(this, &UCarpenterWidgetContractsHolder::OnContractListChanged);
	}
}

void UCarpenterWidgetContractsHolder::OnContractListChanged(const TArray<FCarpenterContractData>& AvailableContracts)
{
	if (!HorizontalBox)
	{
		return;
	}
	HorizontalBox->ClearChildren();
	for (const FCarpenterContractData& CarpenterContractData : AvailableContracts)
	{
		if (UCarpenterWidgetContract* ContractWidget = CreateWidget<UCarpenterWidgetContract>(this, ContractWidgetClass))
		{
			ContractWidget->SetContractData(CarpenterContractData);
			HorizontalBox->AddChild(ContractWidget);
		}
	}
}




