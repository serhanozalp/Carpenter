// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarpenterStructTypes.generated.h"

USTRUCT(BlueprintType)
struct FCarpenterItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float CostAmount;

	UPROPERTY(EditDefaultsOnly)
	FString Name;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct FCarpenterContractData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FCarpenterItemData RequestedItemData;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor RequestedItemColor;

	UPROPERTY(EditDefaultsOnly)
	float RewardAmount;
};
