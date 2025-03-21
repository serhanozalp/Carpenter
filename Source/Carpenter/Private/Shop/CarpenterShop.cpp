// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop/CarpenterShop.h"

#include "Components/ContractSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CarpenterWidgetContractsHolder.h"


ACarpenterShop::ACarpenterShop()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ShopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shop Mesh"));
	SetRootComponent(ShopMesh);
	
	ContractSystemComponent = CreateDefaultSubobject<UContractSystemComponent>(TEXT("Contract System Component"));
	ContractSystemComponent->SetIsReplicated(true);

	AvailableContractsWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Available Contracts Widget"));
	AvailableContractsWidget->SetupAttachment(GetRootComponent());
	AvailableContractsWidget->SetDrawAtDesiredSize(true);
}

void ACarpenterShop::BeginPlay()
{
	Super::BeginPlay();

	if (AvailableContractsWidget)
	{
		if (UCarpenterWidgetContractsHolder* ContractsHolderWidget = Cast<UCarpenterWidgetContractsHolder>(AvailableContractsWidget->GetWidget()))
		{
			ContractsHolderWidget->SetupOnContractListChangedDelegate(ContractSystemComponent);
		}
	}
}


