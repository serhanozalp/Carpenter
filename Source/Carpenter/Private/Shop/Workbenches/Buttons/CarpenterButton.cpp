// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/Buttons/CarpenterButton.h"

ACarpenterButton::ACarpenterButton()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh"));
	SetRootComponent(ButtonMesh);
}

void ACarpenterButton::Interact(ACarpenterCharacter* InteractorCharacter)
{
	OnButtonInteracted.Broadcast(InteractorCharacter, this);
}

void ACarpenterButton::EnableOutline(bool bShouldEnable)
{
	if (!ButtonMesh || !OverlayMaterial)
	{
		return;
	}

	UMaterial* Material = bShouldEnable ? OverlayMaterial : nullptr;
	ButtonMesh->SetOverlayMaterial(Material);
}


