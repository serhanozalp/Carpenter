// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ServerInitialize.h"
#include "ContractSystemComponent.generated.h"

class ACarpenterCharacter;
class UDataAsset_ItemProperties;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnContractListChanged, const TArray<FCarpenterContractData>& AvailableContracts)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARPENTER_API UContractSystemComponent : public UActorComponent, public IServerInitialize
{
	GENERATED_BODY()

public:

	//PROPERTY

	FOnContractListChanged OnContractListChanged;

	//METHOD
	
	UContractSystemComponent();
	virtual void Server_Initialize() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UDataAsset_ItemProperties* GetItemPropertiesDataAsset();
	float Server_CompleteContract(const FCarpenterContractData& ContractToCheck);

private:
	
	//PROPERTY
	
	UPROPERTY(ReplicatedUsing = OnRep_AvailableContracts)
	TArray<FCarpenterContractData> AvailableContracts;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Data")
	TSoftObjectPtr<UDataAsset_ItemProperties> ItemProperties;

	FTimerHandle GenerateContractTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Settings", meta = (ClampMin = "0"))
	int32 MaxContractAmount = 5;
	
	//METHOD

	void Server_GenerateRandomContract();
	void Server_HandleGenerateContractTimer();
	void Server_LoadItemPropertiesDataAsset();
	
	UFUNCTION()
	void OnRep_AvailableContracts();
};
