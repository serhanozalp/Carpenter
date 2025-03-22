// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop/CarpenterShop.h"

#include "Components/ContractSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"
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

	ChipperWorkbench = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chipper Workbench"));
	ChipperWorkbench->SetupAttachment(GetRootComponent());
	PainterWorkbench = CreateDefaultSubobject<UChildActorComponent>(TEXT("Painter Workbench"));
	PainterWorkbench->SetupAttachment(GetRootComponent());
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
	
	if (HasAuthority())
	{
		Server_Initialize();
	}
}

void ACarpenterShop::Server_Initialize()
{
	if (ContractSystemComponent)
	{
		ContractSystemComponent->Server_Initialize();
	}
	
	if (AActor* ChildActor = ChipperWorkbench->GetChildActor())
	{
		if (ACarpenterWorkbenchChipper* WorkbenchChipper = Cast<ACarpenterWorkbenchChipper>(ChildActor))
		{
			WorkbenchChipper->Server_Initialize();
		}
	}
}



