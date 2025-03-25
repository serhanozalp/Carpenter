// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/CarpenterWorkbenchBase.h"

#include "CarpenterTypes/CarpenterEnumTypes.h"
#include "Shop/Items/CarpenterItem.h"

ACarpenterWorkbenchBase::ACarpenterWorkbenchBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	WorkbenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Workbench Mesh"));
	WorkbenchMesh->SetupAttachment(GetRootComponent());

	ItemHolderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Item Holder"));
	ItemHolderComponent->SetupAttachment(GetRootComponent());
}

void ACarpenterWorkbenchBase::Server_Initialize()
{
}

void ACarpenterWorkbenchBase::Server_SetAttachedCarpenterItem(ACarpenterItem* CarpenterItemToAttach)
{
	AttachedCarpenterItem = CarpenterItemToAttach;
	
	if (!AttachedCarpenterItem)
	{
		return;
	}
	
	AttachedCarpenterItem->AttachToComponent(ItemHolderComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AttachedCarpenterItem->Server_SetItemState(ECarpenterItemState::AttachedToWorkbench);
	AttachedCarpenterItem->Server_SetAttachedWorkbench(this);
}

void ACarpenterWorkbenchBase::SetOwningCarpenterShop(ACarpenterShop* CarpenterShop)
{
	OwningCarpenterShop = CarpenterShop;
}

void ACarpenterWorkbenchBase::Server_BindWorkbenchButtonsDelegates()
{
}

