// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/CarpenterWorkbenchBase.h"

ACarpenterWorkbenchBase::ACarpenterWorkbenchBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WorkbenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Workbench Mesh"));
	SetRootComponent(WorkbenchMesh);
}

