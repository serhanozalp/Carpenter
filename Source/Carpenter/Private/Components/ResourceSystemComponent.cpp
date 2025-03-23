// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ResourceSystemComponent.h"

#include "Carpenter/DebugHelper.h"
#include "Net/UnrealNetwork.h"

UResourceSystemComponent::UResourceSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UResourceSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()->HasAuthority())
	{
		OnRep_MoneyAmount();
	}
}

void UResourceSystemComponent::Server_Initialize()
{
	RemainingMoneyAmount = StartingMoneyAmount;
	OnMoneyAmountChanged.Broadcast(RemainingMoneyAmount);
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
	OnMoneyAmountChanged.Broadcast(RemainingMoneyAmount);
	return true;
}

void UResourceSystemComponent::OnRep_MoneyAmount()
{
	OnMoneyAmountChanged.Broadcast(RemainingMoneyAmount);
}


