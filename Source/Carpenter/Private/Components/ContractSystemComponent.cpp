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
	Server_HandleGenerateContractTimer();
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

float UContractSystemComponent::Server_CompleteContract(const FCarpenterContractData& ContractToCheck)
{
	for (int32 i = 0; i < AvailableContracts.Num(); i++)
	{
		if (ContractToCheck.RequestedItemData.Mesh == AvailableContracts[i].RequestedItemData.Mesh)
		{
			float RewardAmount = AvailableContracts[i].RewardAmount * 0.5;
			AvailableContracts.RemoveAt(i);
			OnRep_AvailableContracts();
			Server_HandleGenerateContractTimer();
			return RewardAmount;
		}
	}
	return 0.0f;
}

void UContractSystemComponent::Server_GenerateRandomContract()
{
	if (!ItemProperties.IsValid())
	{
		return;
	}
	Debug::Print("Contract Generated");
	FCarpenterContractData RandomContract;
	RandomContract.RequestedItemData = *ItemProperties->GetRandomItemData();
	RandomContract.RequestedItemColor = *ItemProperties->GetRandomColor();
	float RewardMultiplier = FMath::RandRange(2.2f, 2.6f);
	RandomContract.RewardAmount = RandomContract.RequestedItemData.CostAmount * RewardMultiplier;
	
	AvailableContracts.Add(RandomContract);
	OnRep_AvailableContracts();
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
		else if (AvailableContracts.Num() < MaxContractAmount && !World->GetTimerManager().IsTimerActive(GenerateContractTimerHandle))
		{
			World->GetTimerManager().SetTimer(GenerateContractTimerHandle, this, &UContractSystemComponent::Server_GenerateRandomContract, 5.0f, true);
		}
	}
}

void UContractSystemComponent::OnRep_AvailableContracts()
{
	OnContractListChanged.Broadcast(AvailableContracts);
}