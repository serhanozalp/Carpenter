// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/CarpenterWorkbenchBase.h"

ACarpenterWorkbenchBase::ACarpenterWorkbenchBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	WorkbenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Workbench Mesh"));
	WorkbenchMesh->SetupAttachment(GetRootComponent());
}

void ACarpenterWorkbenchBase::Server_Initialize()
{
}

void ACarpenterWorkbenchBase::SetOwningCarpenterShop(ACarpenterShop* CarpenterShop)
{
	if (CarpenterShop)
	{
		OwningCarpenterShop = CarpenterShop;
	}
}

