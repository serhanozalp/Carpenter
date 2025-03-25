// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarpenterButton.h"
#include "CarpenterColorableButton.generated.h"

UCLASS()
class CARPENTER_API ACarpenterColorableButton : public ACarpenterButton
{
	GENERATED_BODY()

public:
	
	ACarpenterColorableButton();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void Server_SetColorVectorToApply(const FVector& ColorVector);
	FORCEINLINE FVector GetColorVector() const { return ColorVectorToApply; }

private:

	//PROPERTY
	
	UPROPERTY(ReplicatedUsing = OnRep_ColorVectorToApply)
	FVector ColorVectorToApply;

	//METHOD
	
	UFUNCTION()
	void OnRep_ColorVectorToApply();
};
