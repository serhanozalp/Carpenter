// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"

#include "Carpenter/DebugHelper.h"
#include "Components/ContractSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterShop.h"
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

	BindButtonDelegates();
}

void ACarpenterWorkbenchChipper::OnLeftButtonClicked()
{
	Debug::Print("OnLeftButtonClicked");
	ServerRPC_LeftButtonClicked();
}

void ACarpenterWorkbenchChipper::OnRightButtonClicked()
{
	Debug::Print("OnRightButtonClicked");
	ServerRPC_RightButtonClicked();
}

void ACarpenterWorkbenchChipper::OnBuildButtonClicked()
{
	Debug::Print("OnBuildButtonClicked");
	ServerRPC_BuildButtonClicked();
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

void ACarpenterWorkbenchChipper::ServerRPC_LeftButtonClicked_Implementation()
{
	Debug::Print("ACarpenterWorkbenchChipper::ServerRPC_LeftButtonClicked");
	SelectedItemIndex = FMath::Clamp(SelectedItemIndex-1, 0, CarpenterItemDataList.Num() - 1);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::ServerRPC_RightButtonClicked_Implementation()
{
	SelectedItemIndex = FMath::Clamp(SelectedItemIndex+  1, 0, CarpenterItemDataList.Num() - 1);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::ServerRPC_BuildButtonClicked_Implementation()
{
}

void ACarpenterWorkbenchChipper::Server_SetSelectedItemIndex(int32 ItemIndex)
{
	SelectedItemIndex = ItemIndex;
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

void ACarpenterWorkbenchChipper::BindButtonDelegates()
{
	if (ACarpenterWorkshopButtonBase* LeftButton = Cast<ACarpenterWorkshopButtonBase>(LeftButtonComponent->GetChildActor()))
	{
			LeftButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::OnLeftButtonClicked);
	}
	if (ACarpenterWorkshopButtonBase* RightButton = Cast<ACarpenterWorkshopButtonBase>(RightButtonComponent->GetChildActor()))
	{
		RightButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::OnRightButtonClicked);
	}
	if (ACarpenterWorkshopButtonBase* BuildButton = Cast<ACarpenterWorkshopButtonBase>(BuildButtonComponent->GetChildActor()))
	{
		BuildButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::OnBuildButtonClicked);
	}
	
}

void ACarpenterWorkbenchChipper::OnRep_SelectedItemIndex()
{
	Debug::Print("Client, Selected Item Changed");
	HandleItemDisplayWidget();
}
