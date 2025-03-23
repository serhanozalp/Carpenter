// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"

#include "Carpenter/DebugHelper.h"
#include "CarpenterTypes/CarpenterEnumTypes.h"
#include "Components/ContractSystemComponent.h"
#include "Components/ResourceSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterShop.h"
#include "Shop/Items/CarpenterItem.h"
#include "Shop/Workbenches/Buttons/CarpenterWorkshopButtonBase.h"
#include "Widgets/Shop/Workbenches/CarpenterWidgetChipperDisplay.h"

ACarpenterWorkbenchChipper::ACarpenterWorkbenchChipper()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftButtonComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Button"));
	LeftButtonComponent->SetupAttachment(GetRootComponent());

	RightButtonComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Button"));
	RightButtonComponent->SetupAttachment(GetRootComponent());

	BuildButtonComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Build Button"));
	BuildButtonComponent->SetupAttachment(GetRootComponent());

	ItemDisplayWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item Display"));
	ItemDisplayWidgetComponent->SetupAttachment(GetRootComponent());
	ItemDisplayWidgetComponent->SetDrawAtDesiredSize(true);
	ItemDisplayWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACarpenterWorkbenchChipper::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Server_BindButtonDelegates();
	}
	else
	{
		OnRep_SelectedItemIndex();
	}
}

void ACarpenterWorkbenchChipper::Server_OnLeftButtonClicked(APawn* InteractorPawn)
{
	Server_SetSelectedItemIndex(--SelectedItemIndex);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::Server_OnRightButtonClicked(APawn* InteractorPawn)
{
	Server_SetSelectedItemIndex(++SelectedItemIndex);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::Server_OnBuildButtonClicked(APawn* InteractorPawn)
{
	if (!CarpenterItemClass)
	{
		return;
	}
	Server_HandleItemBuild();
}

void ACarpenterWorkbenchChipper::Server_HandleItemBuild()
{
	if (!bIsEmpty || CarpenterItemDataList.IsEmpty() || !OwningCarpenterShop->GetResourceSystemComponent())
	{
		return;
	}
	
	if (!OwningCarpenterShop->GetResourceSystemComponent()->Server_TryMoneyAmountChange(-CarpenterItemDataList[SelectedItemIndex].CostAmount))
	{
		return;
	}
	
	FVector ItemPosition = ItemHolderComponent->GetComponentLocation();
	FRotator ItemRotation = ItemHolderComponent->GetComponentRotation();
	
	if (ACarpenterItem* CarpenterItem = GetWorld()->SpawnActor<ACarpenterItem>(CarpenterItemClass, ItemPosition, ItemRotation))
	{
		CarpenterItem->Server_SetItemState(ECarpenterItemState::Initial);
		CarpenterItem->Server_SetItemMesh(CarpenterItemDataList[SelectedItemIndex].Mesh);
		CarpenterItem->Server_SetAttachedWorkbench(this);
		bIsEmpty = false;
	}
}

void ACarpenterWorkbenchChipper::Server_Initialize()
{
	if (!OwningCarpenterShop)
	{
		return;
	}
	
	if (UContractSystemComponent* ContractSystemComponent = OwningCarpenterShop->GetContractSystemComponent())
	{
		if (UDataAsset_ItemProperties* ItemPropertiesDataAsset = ContractSystemComponent->GetItemPropertiesDataAsset())
		{
			CarpenterItemDataList = ItemPropertiesDataAsset->CarpenterItemDataList;
		}
	}
	Server_SetSelectedItemIndex(0);
}

void ACarpenterWorkbenchChipper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACarpenterWorkbenchChipper, SelectedItemIndex);
	DOREPLIFETIME_CONDITION(ACarpenterWorkbenchChipper, CarpenterItemDataList, COND_InitialOnly);
}

void ACarpenterWorkbenchChipper::Server_SetSelectedItemIndex(int32 NewItemIndex)
{
	NewItemIndex = FMath::Clamp(NewItemIndex, 0, CarpenterItemDataList.Num() - 1);
	SelectedItemIndex = NewItemIndex;
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::HandleItemDisplayWidget()
{
	if (CarpenterItemDataList.IsEmpty())
	{
		return;
	}

	if (!ItemDisplayWidget && ItemDisplayWidgetComponent->GetWidget())
	{
		ItemDisplayWidget = CastChecked<UCarpenterWidgetChipperDisplay>(ItemDisplayWidgetComponent->GetWidget());
	}
	
	if (SelectedItemIndex < CarpenterItemDataList.Num())
	{
		ItemDisplayWidget->SetItemDisplayText(CarpenterItemDataList[SelectedItemIndex].Name);
	}
}

void ACarpenterWorkbenchChipper::Server_BindButtonDelegates()
{
	if (ACarpenterWorkshopButtonBase* LeftButton = Cast<ACarpenterWorkshopButtonBase>(LeftButtonComponent->GetChildActor()))
	{
			LeftButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnLeftButtonClicked);
	}
	if (ACarpenterWorkshopButtonBase* RightButton = Cast<ACarpenterWorkshopButtonBase>(RightButtonComponent->GetChildActor()))
	{
		RightButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnRightButtonClicked);
	}
	if (ACarpenterWorkshopButtonBase* BuildButton = Cast<ACarpenterWorkshopButtonBase>(BuildButtonComponent->GetChildActor()))
	{
		BuildButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnBuildButtonClicked);
	}
}

void ACarpenterWorkbenchChipper::OnRep_SelectedItemIndex()
{
	HandleItemDisplayWidget();
}
