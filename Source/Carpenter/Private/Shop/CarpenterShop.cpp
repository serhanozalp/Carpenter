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
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	ShopMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shop Mesh Component"));
	ShopMeshComponent->SetupAttachment(GetRootComponent());
	
	ContractSystemComponent = CreateDefaultSubobject<UContractSystemComponent>(TEXT("Contract System Component"));
	ContractSystemComponent->SetIsReplicated(true);

	ResourceSystemComponent =CreateDefaultSubobject<UResourceSystemComponent>(TEXT("Resource System Component"));
	ResourceSystemComponent->SetIsReplicated(true);

	AvailableContractsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Available Contracts Widget"));
	AvailableContractsWidgetComponent->SetupAttachment(GetRootComponent());
	AvailableContractsWidgetComponent->SetDrawAtDesiredSize(true);
	AvailableContractsWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ResourceWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Resource Widget Component"));
	ResourceWidgetComponent->SetupAttachment(GetRootComponent());
	ResourceWidgetComponent->SetDrawAtDesiredSize(true);
	ResourceWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SellButtonComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Sell Zone"));
	SellButtonComponent->SetupAttachment(GetRootComponent());

	ChipperWorkbenchComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chipper Workbench"));
	ChipperWorkbenchComponent->SetupAttachment(GetRootComponent());
	PainterWorkbenchComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Painter Workbench"));
	PainterWorkbenchComponent->SetupAttachment(GetRootComponent());
}

void ACarpenterShop::BeginPlay()
{
	Super::BeginPlay();

	checkf(AvailableContractsWidgetComponent->GetWidget(), TEXT("Available Contract Widget Class is not set!"))
	checkf(ResourceWidgetComponent->GetWidget(), TEXT("Resource Widget Class is not set!"))
	checkf(SellButtonComponent->GetChildActor(), TEXT("Sell Button Component Class is not set!"))
	checkf(ChipperWorkbenchComponent->GetChildActor(), TEXT("Chipper Workbench Component Class is not set!"))
	checkf(PainterWorkbenchComponent->GetChildActor(), TEXT("Painter Workbench Component Class is not set!"))

	if (ACarpenterWorkbenchBase* ChipperWorkbench = Cast<ACarpenterWorkbenchBase>(ChipperWorkbenchComponent->GetChildActor()))
	{
		ChipperWorkbench->SetOwningCarpenterShop(this);
	}

	if (ACarpenterWorkbenchBase* PainterWorkbench = Cast<ACarpenterWorkbenchBase>(PainterWorkbenchComponent->GetChildActor()))
	{
		PainterWorkbench->SetOwningCarpenterShop(this);
	}

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

	ContractSystemComponent->Server_Initialize();
	ResourceSystemComponent->Server_Initialize();

	if (ACarpenterWorkbenchChipper* WorkbenchChipper = Cast<ACarpenterWorkbenchChipper>(ChipperWorkbenchComponent->GetChildActor()))
	{
		WorkbenchChipper->Server_Initialize();
	}
	if (ACarpenterWorkbenchPainter* WorkbenchPainter = Cast<ACarpenterWorkbenchPainter>(PainterWorkbenchComponent->GetChildActor()))
	{
		WorkbenchPainter->Server_Initialize();
	}
	if (ACarpenterButton* SellButton = Cast<ACarpenterButton>(SellButtonComponent->GetChildActor()))
	{
		SellButton->OnButtonInteracted.AddDynamic(this, &ACarpenterShop::Server_OnSellButtonClicked);
	}
}

void ACarpenterShop::Server_OnSellButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
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



