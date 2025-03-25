// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Shop/CarpenterWidgetContractsHolder.h"

#include "Components/Shop/ContractSystemComponent.h"
#include "Components/HorizontalBox.h"
#include "Widgets/Shop/CarpenterWidgetContract.h"

void UCarpenterWidgetContractsHolder::NativeConstruct()
{
	Super::NativeConstruct();

	checkf(IsValid(ContractWidgetClass), TEXT("Contract Widget Class is not set!"))
}

void UCarpenterWidgetContractsHolder::SetupOnContractListChangedDelegate(UContractSystemComponent* ContractSystemComponent)
{
	if (ContractSystemComponent)
	{
		ContractSystemComponent->OnContractListChanged.AddUObject(this, &UCarpenterWidgetContractsHolder::OnContractListChanged);
	}
}

void UCarpenterWidgetContractsHolder::OnContractListChanged(const TArray<FCarpenterContractData>& AvailableContractList)
{
	HorizontalBox->ClearChildren();
	for (const FCarpenterContractData& CarpenterContractData : AvailableContractList)
	{
		if (UCarpenterWidgetContract* ContractWidget = CreateWidget<UCarpenterWidgetContract>(this, ContractWidgetClass))
		{
			ContractWidget->SetContractData(CarpenterContractData);
			HorizontalBox->AddChild(ContractWidget);
		}
	}
}

