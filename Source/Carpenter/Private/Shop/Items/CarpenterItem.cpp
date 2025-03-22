// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Items/CarpenterItem.h"

ACarpenterItem::ACarpenterItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMesh);
}

void ACarpenterItem::Interact(APawn* InteractorPawn)
{
}

void ACarpenterItem::EnableOutline(bool bShouldEnable)
{
	if (OverlayMaterial)
	{
		UMaterial* Material = bShouldEnable ? OverlayMaterial : nullptr;
		ItemMesh->SetOverlayMaterial(Material);
	}
}

