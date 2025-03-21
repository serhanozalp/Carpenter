// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ContractSystemComponent.h"

#include "Carpenter/DebugHelper.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Net/UnrealNetwork.h"

UContractSystemComponent::UContractSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UContractSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		if (GetOwner()->HasAuthority())
		{
			World->GetTimerManager().SetTimer(GenerateContractTimerHandle, this, &UContractSystemComponent::Server_GenerateRandomContract, 5.0f, true);
		}
	}
}

void UContractSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UContractSystemComponent, AvailableContracts);
}

void UContractSystemComponent::Server_GenerateRandomContract()
{
	if (ItemProperties.IsNull())
	{
		return;
	}
	if (!ItemProperties.IsValid())
	{
		if (UDataAsset_ItemProperties* LoadedAsset = ItemProperties.LoadSynchronous())
		{
			if (!LoadedAsset->IsValid())
			{
				return;
			}
		}
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

void UContractSystemComponent::OnRep_AvailableContracts()
{
	Debug::Print(FString::Printf(TEXT("AvailableContracts: %d"), AvailableContracts.Num()));
	OnContractListChanged.Broadcast(AvailableContracts);
}





