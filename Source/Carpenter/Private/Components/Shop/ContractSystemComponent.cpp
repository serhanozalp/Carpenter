// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Shop/ContractSystemComponent.h"

#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterShop.h"

UContractSystemComponent::UContractSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UContractSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContractSystemComponent, AvailableContractList);
}

void UContractSystemComponent::Server_Initialize()
{
	Server_HandleGenerateContractTimer();
}

void UContractSystemComponent::Server_HandleGenerateContractTimer()
{
	if (UWorld* World = GetWorld())
	{
		if (AvailableContractList.Num() == MaxContractAmount)
		{
			World->GetTimerManager().ClearTimer(GenerateContractTimerHandle);
		}
		else if (AvailableContractList.Num() < MaxContractAmount && !World->GetTimerManager().IsTimerActive(GenerateContractTimerHandle))
		{
			World->GetTimerManager().SetTimer(GenerateContractTimerHandle, this, &UContractSystemComponent::Server_GenerateRandomContract, 5.0f, true);
		}
	}
}

float UContractSystemComponent::Server_CompleteContract(const FCarpenterContractData& ContractToCheck)
{
	for (int32 i = 0; i < AvailableContractList.Num(); i++)
	{
		if (ContractToCheck.RequestedItemData.Mesh == AvailableContractList[i].RequestedItemData.Mesh)
		{
			float RewardAmount = AvailableContractList[i].RewardAmount * 0.5;
			AvailableContractList.RemoveAt(i);
			OnRep_AvailableContractList();
			Server_HandleGenerateContractTimer();
			return RewardAmount;
		}
	}
	return 0.0f;
}

void UContractSystemComponent::Server_GenerateRandomContract()
{
	FCarpenterContractData RandomContract;
	
	RandomContract.RequestedItemData = *CachedOwningCarpenterShop->GetItemPropertiesDataAsset()->GetRandomItemData();
	RandomContract.RequestedItemColor = *CachedOwningCarpenterShop->GetItemPropertiesDataAsset()->GetRandomColor();
	float RewardMultiplier = FMath::RandRange(2.2f, 2.6f);
	RandomContract.RewardAmount = RandomContract.RequestedItemData.CostAmount * RewardMultiplier;
	
	AvailableContractList.Add(RandomContract);
	OnRep_AvailableContractList();
	Server_HandleGenerateContractTimer();
}

void UContractSystemComponent::OnRep_AvailableContractList()
{
	OnContractListChanged.Broadcast(AvailableContractList);
}