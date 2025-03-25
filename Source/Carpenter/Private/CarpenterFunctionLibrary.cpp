// Fill out your copyright notice in the Description page of Project Settings.


#include "CarpenterFunctionLibrary.h"

void UCarpenterFunctionLibrary::NativeColorMeshComponent(UMeshComponent* MeshComponent, const FName& ParameterName, const FVector& ColorVector, int32 MaterialIndex)
{
	if (!MeshComponent || !MeshComponent->GetMaterial(MaterialIndex))
	{
		return;
	}

	if (UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(MeshComponent->GetMaterial(MaterialIndex)))
	{
		DynamicMaterial->SetVectorParameterValue(ParameterName, ColorVector);
		return;
	}

	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(MaterialIndex), MeshComponent);
	DynamicMaterial->SetVectorParameterValue(ParameterName, ColorVector);
	MeshComponent->SetMaterial(MaterialIndex, DynamicMaterial);
}

FLinearColor UCarpenterFunctionLibrary::NativeConvertVectorToLinearColor(const FVector& ColorVectorToConvert)
{
	return FLinearColor(ColorVectorToConvert.X, ColorVectorToConvert.Y, ColorVectorToConvert.Z);
}
