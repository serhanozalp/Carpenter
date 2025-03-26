// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/CarpenterWorkbenchChipper.h"

#include "Components/Shop/ResourceSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterShop.h"
#include "Shop/Items/CarpenterItem.h"
#include "Shop/Workbenches/Buttons/CarpenterButton.h"
#include "Widgets/Shop/Workbenches/CarpenterWidgetChipperDisplay.h"

ACarpenterWorkbenchChipper::ACarpenterWorkbenchChipper()
{
	PrimaryActorTick.bCanEverTick = false;

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

	checkf(IsValid(CarpenterItemClass), TEXT("Carpenter Item Class is not set!"))
	checkf(LeftButtonComponent->GetChildActor(), TEXT("Left Button Component Class is not set!"))
	checkf(RightButtonComponent->GetChildActor(), TEXT("Right Button Component Class is not set!"))
	checkf(BuildButtonComponent->GetChildActor(), TEXT("Build Button Component Class is not set!"))
	checkf(ItemDisplayWidgetComponent->GetWidget(), TEXT("Item Display Widget Class is not set!"))
}

void ACarpenterWorkbenchChipper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACarpenterWorkbenchChipper, SelectedItemIndex);
	DOREPLIFETIME_CONDITION(ACarpenterWorkbenchChipper, CarpenterItemDataList, COND_InitialOnly);
}

void ACarpenterWorkbenchChipper::Server_Initialize()
{
	if (!OwningCarpenterShop)
	{
		return;
	}

	if (UDataAsset_ItemProperties* ItemPropertiesDataAsset = OwningCarpenterShop->GetItemPropertiesDataAsset())
	{
		CarpenterItemDataList = ItemPropertiesDataAsset->CarpenterItemDataList;
	}

	Server_BindWorkbenchButtonsDelegates();
	Server_SetSelectedItemIndex(0);
}

void ACarpenterWorkbenchChipper::Server_BindWorkbenchButtonsDelegates()
{
	if (ACarpenterButton* LeftButton = Cast<ACarpenterButton>(LeftButtonComponent->GetChildActor()))
	{
		LeftButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnLeftButtonClicked);
	}
	if (ACarpenterButton* RightButton = Cast<ACarpenterButton>(RightButtonComponent->GetChildActor()))
	{
		RightButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnRightButtonClicked);
	}
	if (ACarpenterButton* BuildButton = Cast<ACarpenterButton>(BuildButtonComponent->GetChildActor()))
	{
		BuildButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchChipper::Server_OnBuildButtonClicked);
	}
}

void ACarpenterWorkbenchChipper::Server_OnLeftButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
	Server_SetSelectedItemIndex(SelectedItemIndex - 1);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::Server_OnRightButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
	Server_SetSelectedItemIndex(SelectedItemIndex + 1);
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::Server_OnBuildButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
	if (!IsEmpty())
	{
		return;
	}
	
	Server_HandleItemBuild();
}

void ACarpenterWorkbenchChipper::Server_HandleItemBuild()
{
	if (!OwningCarpenterShop->GetResourceSystemComponent()->Server_TryMoneyAmountChange(-CarpenterItemDataList[SelectedItemIndex].CostAmount) || !GetWorld())
	{
		return;
	}
	
	if (ACarpenterItem* CarpenterItem = GetWorld()->SpawnActor<ACarpenterItem>(CarpenterItemClass, FVector::ZeroVector, FRotator::ZeroRotator))
	{
		CarpenterItem->Server_SetItemMesh(CarpenterItemDataList[SelectedItemIndex].Mesh);
		Server_SetAttachedCarpenterItem(CarpenterItem);
	}
}

void ACarpenterWorkbenchChipper::Server_SetSelectedItemIndex(int32 NewItemIndex)
{
	NewItemIndex = FMath::Clamp(NewItemIndex, 0, CarpenterItemDataList.Num() - 1);
	SelectedItemIndex = NewItemIndex;
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::HandleItemDisplayWidget()
{
	if (!CachedItemDisplayWidget)
	{
		CachedItemDisplayWidget = CastChecked<UCarpenterWidgetChipperDisplay>(ItemDisplayWidgetComponent->GetWidget());
	}
	
	if (SelectedItemIndex < CarpenterItemDataList.Num())
	{
		CachedItemDisplayWidget->SetItemDisplayText(CarpenterItemDataList[SelectedItemIndex].Name);
	}
}

void ACarpenterWorkbenchChipper::OnRep_SelectedItemIndex()
{
	HandleItemDisplayWidget();
}

void ACarpenterWorkbenchChipper::OnRep_CarpenterItemDataList()
{
	OnRep_SelectedItemIndex();
}
