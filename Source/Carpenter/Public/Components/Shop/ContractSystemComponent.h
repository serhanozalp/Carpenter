// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/ActorComponent.h"
#include "Components/CarpenterShopActorComponent.h"
#include "ContractSystemComponent.generated.h"

class ACarpenterCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnContractListChanged, const TArray<FCarpenterContractData>& AvailableContracts)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARPENTER_API UContractSystemComponent : public UCarpenterShopActorComponent
{
	GENERATED_BODY()

public:

	//PROPERTY

	FOnContractListChanged OnContractListChanged;

	//METHOD
	
	UContractSystemComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void Server_Initialize() override;
	float Server_CompleteContract(const FCarpenterContractData& ContractToCheck);

private:
	
	//PROPERTY
	
	UPROPERTY(ReplicatedUsing = OnRep_AvailableContractList)
	TArray<FCarpenterContractData> AvailableContractList;

	FTimerHandle GenerateContractTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0"))
	int32 MaxContractAmount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0"))
	float MinContractRewardMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0"))
	float MaxContractRewardMultiplier = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0"))
	float MinContractTimerCooldown = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0"))
	float MaxContractTimerCooldown = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|ContractSystemComponent|Settings", meta = (ClampMin = "0", ClampMax = "1"))
	float ColorMismatchPenalty = 0.5f;
	
	//METHOD

	void Server_GenerateRandomContract();
	void Server_HandleGenerateContractTimer();
	
	UFUNCTION()
	void OnRep_AvailableContractList();
};
