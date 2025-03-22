// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Shop/Workbenches/CarpenterWidgetChipperDisplay.h"

#include "Components/TextBlock.h"

void UCarpenterWidgetChipperDisplay::SetItemDisplayText(const FString& DisplayText)
{
	if (ItemDisplayText)
	{
		ItemDisplayText->SetText(FText::FromString(DisplayText));
	}
}
