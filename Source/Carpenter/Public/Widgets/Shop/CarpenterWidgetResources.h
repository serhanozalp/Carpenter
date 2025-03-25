// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CarpenterWidgetResources.generated.h"

class UTextBlock;
class UResourceSystemComponent;

UCLASS()
class CARPENTER_API UCarpenterWidgetResources : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void OnMoneyAmountChanged(float NewMoneyAmount);
	void SetupOnResourcesChangedDelegate(UResourceSystemComponent* ResourceSystemComponent);

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MoneyAmountText;
};
