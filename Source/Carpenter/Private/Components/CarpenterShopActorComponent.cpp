// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CarpenterShopActorComponent.h"

#include "Shop/CarpenterShop.h"

UCarpenterShopActorComponent::UCarpenterShopActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCarpenterShopActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CachedOwningCarpenterShop = CastChecked<ACarpenterShop>(GetOwner());
}

void UCarpenterShopActorComponent::Server_Initialize()
{
}

