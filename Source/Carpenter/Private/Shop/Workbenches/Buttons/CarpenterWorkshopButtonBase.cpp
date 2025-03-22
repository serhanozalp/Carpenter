// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/Buttons/CarpenterWorkshopButtonBase.h"

ACarpenterWorkshopButtonBase::ACarpenterWorkshopButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	SetRootComponent(ButtonMesh);
}

void ACarpenterWorkshopButtonBase::Interact(APawn* InteractorPawn)
{
	OnButtonInteracted.Broadcast();
}

void ACarpenterWorkshopButtonBase::EnableOutline(bool bShouldEnable)
{
	if (OverlayMaterial)
	{
		UMaterial* Material = bShouldEnable ? OverlayMaterial : nullptr;
		ButtonMesh->SetOverlayMaterial(Material);
	}
}


