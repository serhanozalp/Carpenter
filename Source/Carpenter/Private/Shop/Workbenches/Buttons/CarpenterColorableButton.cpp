// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/Buttons/CarpenterColorableButton.h"

#include "Net/UnrealNetwork.h"


ACarpenterColorableButton::ACarpenterColorableButton()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACarpenterColorableButton::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACarpenterColorableButton, ColorVectorToApply, COND_InitialOnly);
}

void ACarpenterColorableButton::Server_SetColorVectorToApply(const FVector& ColorVector)
{
	ColorVectorToApply = ColorVector;
	OnRep_ColorVectorToApply();
}

void ACarpenterColorableButton::OnRep_ColorVectorToApply()
{
	if (!ButtonMesh)
	{
		return;
	}
	
	if (UMaterialInterface* CurrentMaterial = ButtonMesh->GetMaterial(0))
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(CurrentMaterial, this);
		DynamicMaterial->SetVectorParameterValue(FName("ColorParameter"), ColorVectorToApply);
		ButtonMesh->SetMaterial(0, DynamicMaterial);
	}
}

