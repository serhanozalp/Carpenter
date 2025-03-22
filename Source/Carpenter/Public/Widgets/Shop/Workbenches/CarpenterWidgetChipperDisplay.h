// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CarpenterWidgetChipperDisplay.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CARPENTER_API UCarpenterWidgetChipperDisplay : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetItemDisplayText(const FString& DisplayText);

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDisplayText;
};
