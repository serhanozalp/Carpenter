// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ServerInitialize.h"
#include "ResourceSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoneyAmountChanged, float MoneyAmount)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARPENTER_API UResourceSystemComponent : public UActorComponent, public IServerInitialize
{
	GENERATED_BODY()

public:

	//PROPERTY

	FOnMoneyAmountChanged OnMoneyAmountChanged;
	
	//METHOD
	
	UResourceSystemComponent();
	virtual void BeginPlay() override;
	virtual void Server_Initialize() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	bool Server_TryMoneyAmountChange(float ChangeAmount);
	
private:

	//PROPERTY
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Settings" , meta = (ClampMin = "0"))
	float StartingMoneyAmount = 400.0f;
	
	UPROPERTY(ReplicatedUsing = OnRep_MoneyAmount)
	float RemainingMoneyAmount;

	//METHOD

	UFUNCTION()
	void OnRep_MoneyAmount();
};
