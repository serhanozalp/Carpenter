// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Items/CarpenterItem.h"

#include "CarpenterFunctionLibrary.h"
#include "Carpenter/DebugHelper.h"
#include "CarpenterTypes/CarpenterEnumTypes.h"
#include "Character/CarpenterCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterWorkbenchBase.h"

ACarpenterItem::ACarpenterItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMeshComponent);
	ItemMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACarpenterItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACarpenterItem, ItemState);
	DOREPLIFETIME_CONDITION(ACarpenterItem, ItemMeshToApply, COND_InitialOnly);
	DOREPLIFETIME(ACarpenterItem, ColorVectorToApply);
}

void ACarpenterItem::Interact(ACarpenterCharacter* InteractorCharacter)
{
	if (!InteractorCharacter)
	{
		return;
	}

	InteractorCharacter->Server_SetCarriedCarpenterItem(this);
}

void ACarpenterItem::EnableOutline(bool bShouldEnable)
{
	if (OverlayMaterial)
	{
		UMaterial* Material = bShouldEnable ? OverlayMaterial : nullptr;
		ItemMeshComponent->SetOverlayMaterial(Material);
	}
}

void ACarpenterItem::Server_SetItemMesh(UStaticMesh* InItemMesh)
{
	ItemMeshComponent->SetStaticMesh(InItemMesh);
	ItemMeshToApply = InItemMesh;
}

void ACarpenterItem::Server_SetItemColor(const FVector& ColorVector)
{
	ColorVectorToApply = ColorVector;
	OnRep_ColorVectorToApply();
}

void ACarpenterItem::Server_SetItemState(ECarpenterItemState InItemState)
{
	if (ItemState != InItemState)
	{
		ItemState = InItemState;
		HandleItemState();
	}
}

void ACarpenterItem::Server_SetAttachedWorkbench(ACarpenterWorkbenchBase* Workbench)
{
	if (!Workbench)
	{
		AttachedWorkBench->Server_SetAttachedCarpenterItem(nullptr);
	}
	
	AttachedWorkBench = Workbench;
}

void ACarpenterItem::OnRep_ItemMeshToApply()
{
	if (ItemMeshToApply)
	{
		ItemMeshComponent->SetStaticMesh(ItemMeshToApply);
	}
}

void ACarpenterItem::OnRep_ColorVectorToApply()
{
	UCarpenterFunctionLibrary::NativeColorMeshComponent(ItemMeshComponent, FName("ColorParameter"), ColorVectorToApply, 0);
}

void ACarpenterItem::OnRep_ItemState()
{
	HandleItemState();
}

void ACarpenterItem::HandleItemState()
{
	switch (ItemState)
	{
		case ECarpenterItemState::AttachedToWorkbench:
			ItemMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
			ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
		case ECarpenterItemState::PickedUp:
			ItemMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		break;
		case ECarpenterItemState::Dropped:
		break;
		
	}
}

