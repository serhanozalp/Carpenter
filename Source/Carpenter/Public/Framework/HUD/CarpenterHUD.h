// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CarpenterHUD.generated.h"

class UCarpenterWidgetHUD;

UCLASS()
class CARPENTER_API ACarpenterHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|CarpenterHUD|Settings", meta=(AllowPrivateAccess=true))
	TSubclassOf<UCarpenterWidgetHUD> HUDWidgetClass;
};
