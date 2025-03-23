// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ContractSystemComponent.h"

#include "Carpenter/DebugHelper.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Net/UnrealNetwork.h"

UContractSystemComponent::UContractSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UContractSystemComponent::Server_Initialize()
{
	Server_LoadItemPropertiesDataAsset();
	Server_StartGenerateContractTimer();
}

void UContractSystemComponent::Server_LoadItemPropertiesDataAsset()
{
	if (ItemProperties.IsNull())
	{
		return;
	}
	if (!ItemProperties.IsValid())
	{
		ItemProperties.LoadSynchronous();
	}
}

void UContractSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContractSystemComponent, AvailableContracts);
}

UDataAsset_ItemProperties* UContractSystemComponent::GetItemPropertiesDataAsset()
{
	Server_LoadItemPropertiesDataAsset();
	return ItemProperties.Get();
}

void UContractSystemComponent::Server_GenerateRandomContract()
{
	if (!ItemProperties.IsValid())
	{
		return;
	}
	
	FCarpenterContractData RandomContract;
	RandomContract.RequestedItemData = *ItemProperties->GetRandomItemData();
	RandomContract.RequestedItemColor = *ItemProperties->GetRandomColor();
	float RewardMultiplier = FMath::RandRange(2.2f, 2.6f);
	RandomContract.RewardAmount = RandomContract.RequestedItemData.CostAmount * RewardMultiplier;
	
	AvailableContracts.Add(RandomContract);
	OnContractListChanged.Broadcast(AvailableContracts);
	Server_HandleGenerateContractTimer();
}

void UContractSystemComponent::Server_HandleGenerateContractTimer()
{
	if (UWorld* World = GetWorld())
	{
		if (AvailableContracts.Num() == MaxContractAmount)
		{
			World->GetTimerManager().ClearTimer(GenerateContractTimerHandle);
		}
	}
}

void UContractSystemComponent::Server_StartGenerateContractTimer()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(GenerateContractTimerHandle, this, &UContractSystemComponent::Server_GenerateRandomContract, 5.0f, true);
	}
}

void UContractSystemComponent::OnRep_AvailableContracts()
{
	OnContractListChanged.Broadcast(AvailableContracts);
}


