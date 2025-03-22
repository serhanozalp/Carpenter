// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"

#include "Carpenter/DebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Shop/CarpenterShop.h"

ACarpenterWorkbenchChipper::ACarpenterWorkbenchChipper()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftButton = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Button"));
	LeftButton->SetupAttachment(GetRootComponent());

	RightButton = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Button"));
	RightButton->SetupAttachment(GetRootComponent());

	ItemDisplayWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item Display"));
	ItemDisplayWidget->SetupAttachment(GetRootComponent());
	ItemDisplayWidget->SetDrawAtDesiredSize(true);
}

void ACarpenterWorkbenchChipper::Server_Initialize()
{
	if (!OwningCarpenterShop)
	{
		return;
	}
	if (UContractSystemComponent* ContractSystemComponent = OwningCarpenterShop->GetContractSystemComponent())
	{
	}
}

void ACarpenterWorkbenchChipper::LeftButtonClicked_Implementation()
{
	Debug::Print("LeftButtonClicked_Implementation");
}

void ACarpenterWorkbenchChipper::RightButtonClicked_Implementation()
{
	Debug::Print("RightButtonClicked_Implementation");
}




