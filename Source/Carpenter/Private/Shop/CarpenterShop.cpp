// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop/CarpenterShop.h"

#include "Character/CarpenterCharacter.h"
#include "Components/Shop/ContractSystemComponent.h"
#include "Components/Shop/ResourceSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"
#include "Shop/Workbenches/CarpenterWorkbenchPainter.h"
#include "Shop/Workbenches/Buttons/CarpenterButton.h"
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

	if (UCarpenterWidgetContractsHolder* ContractsHolderWidget = Cast<UCarpenterWidgetContractsHolder>(AvailableContractsWidgetComponent->GetWidget()))
	{
		ContractsHolderWidget->SetupOnContractListChangedDelegate(ContractSystemComponent);
	}
		
	if (UCarpenterWidgetResources* ResourcesWidget = Cast<UCarpenterWidgetResources>(ResourceWidgetComponent->GetWidget()))
	{
		ResourcesWidget->SetupOnResourcesChangedDelegate(ResourceSystemComponent);
	}
	
	if (HasAuthority())
	{
		Server_Initialize();
	}
}

void ACarpenterShop::Server_Initialize()
{
	Server_LoadItemPropertiesDataAsset();
		
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

	if (AActor* ChildActor = PainterWorkbench->GetChildActor())
	{
		if (ACarpenterWorkbenchPainter* WorkbenchPainter = Cast<ACarpenterWorkbenchPainter>(ChildActor))
		{
			WorkbenchPainter->Server_Initialize();
		}
	}

	if (AActor* ChildActor = SellZone->GetChildActor())
	{
		if (ACarpenterButton* SellZoneButton = Cast<ACarpenterButton>(ChildActor))
		{
			SellZoneButton->OnButtonInteracted.AddDynamic(this, &ACarpenterShop::Server_OnSellZoneButtonClicked);
		}
	}
}

void ACarpenterShop::Server_OnSellZoneButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
	if (!InteractorCharacter)
	{
		return;
	}

	float RewardAmount = InteractorCharacter->Server_SellItem(ContractSystemComponent);
	if (RewardAmount > 0.0f)
	{
		ResourceSystemComponent->Server_TryMoneyAmountChange(RewardAmount);
	}
}

void ACarpenterShop::Server_LoadItemPropertiesDataAsset()
{
	checkf(!ItemPropertiesDataAsset.IsNull(), TEXT("Item Properties Data Asset is not assigned!"))
	if (!ItemPropertiesDataAsset.IsValid())
	{
		ItemPropertiesDataAsset.LoadSynchronous();
	}
	checkf(ItemPropertiesDataAsset.Get()->IsValid(), TEXT("Item Properties Data Asset is not valid! Add colors and item data!"))
}



