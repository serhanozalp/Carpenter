// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/Buttons/CarpenterButton.h"

ACarpenterButton::ACarpenterButton()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ButtonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Mesh Component"));
	SetRootComponent(ButtonMeshComponent);
}

void ACarpenterButton::Interact(ACarpenterCharacter* InteractorCharacter)
{
	OnButtonInteracted.Broadcast(InteractorCharacter, this);
}

void ACarpenterButton::EnableOutline(bool bShouldEnable)
{
	if (!OverlayMaterial)
	{
		return;
	}

	UMaterial* Material = bShouldEnable ? OverlayMaterial : nullptr;
	ButtonMeshComponent->SetOverlayMaterial(Material);
}


