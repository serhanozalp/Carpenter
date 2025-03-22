// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Items/CarpenterItem.h"
#include "Net/UnrealNetwork.h"

ACarpenterItem::ACarpenterItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
		
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMeshComponent);
}

void ACarpenterItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACarpenterItem, ItemMeshToApply, COND_InitialOnly);
}

void ACarpenterItem::Interact(APawn* InteractorPawn)
{
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
	if (InItemMesh)
	{
		ItemMeshComponent->SetStaticMesh(InItemMesh);
		ItemMeshToApply = InItemMesh;
	}
}

void ACarpenterItem::OnRep_ItemMeshToApply()
{
	if (ItemMeshToApply)
	{
		ItemMeshComponent->SetStaticMesh(ItemMeshToApply);
	}
}


