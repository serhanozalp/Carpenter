// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Shop/ContractSystemComponent.h"

#include "Net/UnrealNetwork.h"
#include "Shop/CarpenterShop.h"

UContractSystemComponent::UContractSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
		else if (AvailableContractList.Num() < MaxContractAmount)
		{
			float ContractTimerValueCooldown = FMath::RandRange(MinContractTimerCooldown, MaxContractTimerCooldown);
			World->GetTimerManager().SetTimer(GenerateContractTimerHandle, this, &UContractSystemComponent::Server_GenerateRandomContract, ContractTimerValueCooldown, true);
		}
	}
}

float UContractSystemComponent::Server_CompleteContract(const FCarpenterContractData& ContractToCheck)
{
	float RewardMultiplier = 0.0f;
	int32 ContractToCompleteIndex = -1;
	
	for (int32 i = 0; i < AvailableContractList.Num(); i++)
	{
		if (ContractToCheck.RequestedItemData.Mesh != AvailableContractList[i].RequestedItemData.Mesh)
		{
			continue;
		}

		RewardMultiplier = ColorMismatchPenalty;
		ContractToCompleteIndex = i;

		if (ContractToCheck.RequestedItemColor == AvailableContractList[i].RequestedItemColor)
		{
			RewardMultiplier = 1.0f;
			ContractToCompleteIndex = i;
			break;
		}
	}

	if (ContractToCompleteIndex == -1)
	{
		return 0.0f;
	}

	float RewardAmount = AvailableContractList[ContractToCompleteIndex].RewardAmount * RewardMultiplier;
	AvailableContractList.RemoveAt(ContractToCompleteIndex);
	OnRep_AvailableContractList();
	Server_HandleGenerateContractTimer();
	return RewardAmount;
}

void UContractSystemComponent::Server_GenerateRandomContract()
{
	FCarpenterContractData RandomContract;
	
	RandomContract.RequestedItemData = *CachedOwningCarpenterShop->GetItemPropertiesDataAsset()->GetRandomItemData();
	RandomContract.RequestedItemColor = *CachedOwningCarpenterShop->GetItemPropertiesDataAsset()->GetRandomColor();
	float ContractRewardMultiplier = FMath::RandRange(MinContractRewardMultiplier, MaxContractRewardMultiplier);
	RandomContract.RewardAmount = RandomContract.RequestedItemData.CostAmount * ContractRewardMultiplier;
	
	AvailableContractList.Add(RandomContract);
	OnRep_AvailableContractList();
	Server_HandleGenerateContractTimer();
}

void UContractSystemComponent::OnRep_AvailableContractList()
{
	OnContractListChanged.Broadcast(AvailableContractList);
}