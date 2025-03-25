// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CarpenterWidgetContractsHolder.generated.h"

class UHorizontalBox;
class UCarpenterWidgetContract;
struct FCarpenterContractData;
class UContractSystemComponent;

UCLASS()
class CARPENTER_API UCarpenterWidgetContractsHolder : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetupOnContractListChangedDelegate(UContractSystemComponent* ContractSystemComponent);
	void OnContractListChanged(const TArray<FCarpenterContractData>& AvailableContractList);

protected:
	
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Settings")
	TSubclassOf<UCarpenterWidgetContract> ContractWidgetClass;
};
