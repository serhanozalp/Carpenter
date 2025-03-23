// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop/CarpenterShop.h"

#include "Carpenter/DebugHelper.h"
#include "Character/CarpenterCharacter.h"
#include "Components/ContractSystemComponent.h"
#include "Components/ResourceSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"
#include "Shop/Workbenches/Buttons/CarpenterWorkshopButtonBase.h"
#include "Widgets/Shop/CarpenterWidgetContractsHolder.h"
#include "Widgets/Shop/CarpenterWidgetResources.h"


ACarpenterShop::ACarpenterShop()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	ShopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shop Mesh"));
	ShopMesh->SetupAttachment(GetRootComponent());
	
	ContractSystemComponent = CreateDefaultSubobject<UContractSystemComponent>(TEXT("Contract System Component"));
	ContractSystemComponent->SetIsReplicated(true);

	ResourceSystemComponent =CreateDefaultSubobject<UResourceSystemComponent>(TEXT("Resource System Component"));
	ResourceSystemComponent->SetIsReplicated(true);

	AvailableContractsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Available Contracts Widget"));
	AvailableContractsWidgetComponent->SetupAttachment(GetRootComponent());
	AvailableContractsWidgetComponent->SetDrawAtDesiredSize(true);

	ResourceWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Resource Widget Component"));
	ResourceWidgetComponent->SetupAttachment(GetRootComponent());
	ResourceWidgetComponent->SetDrawAtDesiredSize(true);

	SellZone = CreateDefaultSubobject<UChildActorComponent>(TEXT("Sell Zone"));
	SellZone->SetupAttachment(GetRootComponent());

	ChipperWorkbench = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chipper Workbench"));
	ChipperWorkbench->SetupAttachment(GetRootComponent());
	PainterWorkbench = CreateDefaultSubobject<UChildActorComponent>(TEXT("Painter Workbench"));
	PainterWorkbench->SetupAttachment(GetRootComponent());
}

void ACarpenterShop::BeginPlay()
{
	Super::BeginPlay();

	if (AvailableContractsWidgetComponent)
	{
		if (UCarpenterWidgetContractsHolder* ContractsHolderWidget = Cast<UCarpenterWidgetContractsHolder>(AvailableContractsWidgetComponent->GetWidget()))
		{
			ContractsHolderWidget->SetupOnContractListChangedDelegate(ContractSystemComponent);
		}
	}

	if (ResourceWidgetComponent)
	{
		if (UCarpenterWidgetResources* ResourcesWidget = Cast<UCarpenterWidgetResources>(ResourceWidgetComponent->GetWidget()))
		{
			ResourcesWidget->SetupOnResourcesChangedDelegate(ResourceSystemComponent);
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

	if (ResourceSystemComponent)
	{
		ResourceSystemComponent->Server_Initialize();
	}
	
	if (AActor* ChildActor = ChipperWorkbench->GetChildActor())
	{
		if (ACarpenterWorkbenchChipper* WorkbenchChipper = Cast<ACarpenterWorkbenchChipper>(ChildActor))
		{
			WorkbenchChipper->Server_Initialize();
		}
	}

	if (AActor* ChildActor = SellZone->GetChildActor())
	{
		if (ACarpenterWorkshopButtonBase* SellZoneButton = Cast<ACarpenterWorkshopButtonBase>(ChildActor))
		{
			SellZoneButton->OnButtonInteracted.AddDynamic(this, &ACarpenterShop::Server_OnSellZoneButtonClicked);
		}
	}
}

void ACarpenterShop::Server_OnSellZoneButtonClicked(APawn* InteractorPawn)
{
	if (!InteractorPawn)
	{
		return;
	}
	
	if (ACarpenterCharacter* CarpenterCharacter = Cast<ACarpenterCharacter>(InteractorPawn))
	{
		float RewardAmount = CarpenterCharacter->Server_SellItem(ContractSystemComponent);
		if (RewardAmount > 0.0f)
		{
			ResourceSystemComponent->Server_TryMoneyAmountChange(RewardAmount);
		}
	}
}



