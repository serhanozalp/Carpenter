// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CarpenterFunctionLibrary.generated.h"

UCLASS()
class CARPENTER_API UCarpenterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void NativeColorMeshComponent(UMeshComponent* MeshComponent, const FName& ParameterName, const FVector& ColorVector, int32 MaterialIndex);
	static FLinearColor NativeConvertVectorToLinearColor(const FVector& ColorVectorToConvert);
};
