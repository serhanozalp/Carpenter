// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Shop/ResourceSystemComponent.h"

#include "Net/UnrealNetwork.h"

UResourceSystemComponent::UResourceSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UResourceSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GetOwner()->HasAuthority())
	{
		OnRep_RemainingMoneyAmount();
	}
}

void UResourceSystemComponent::Server_Initialize()
{
	RemainingMoneyAmount = StartingMoneyAmount;
	OnRep_RemainingMoneyAmount();
}

void UResourceSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UResourceSystemComponent, RemainingMoneyAmount);
}

bool UResourceSystemComponent::Server_TryMoneyAmountChange(float ChangeAmount)
{
	float NewMoneyAmount = RemainingMoneyAmount + ChangeAmount;
	if (NewMoneyAmount < 0.0f)
	{
		return false;
	}
	RemainingMoneyAmount = NewMoneyAmount;
	OnRep_RemainingMoneyAmount();
	return true;
}

void UResourceSystemComponent::OnRep_RemainingMoneyAmount()
{
	OnMoneyAmountChanged.Broadcast(RemainingMoneyAmount);
}


