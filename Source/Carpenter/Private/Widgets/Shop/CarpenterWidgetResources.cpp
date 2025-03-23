// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Shop/CarpenterWidgetResources.h"

#include "Components/ResourceSystemComponent.h"
#include "Components/TextBlock.h"

void UCarpenterWidgetResources::SetupOnResourcesChangedDelegate(UResourceSystemComponent* ResourceSystemComponent)
{
	if (ResourceSystemComponent)
	{
		ResourceSystemComponent->OnMoneyAmountChanged.AddUObject(this, &UCarpenterWidgetResources::OnMoneyAmountChanged);
	}
}

void UCarpenterWidgetResources::OnMoneyAmountChanged(float NewMoneyAmount)
{
	MoneyAmountText->SetText(FText::AsNumber(NewMoneyAmount));
}
