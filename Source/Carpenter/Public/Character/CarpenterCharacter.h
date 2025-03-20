// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carpenter/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "CarpenterCharacter.generated.h"

class UContractSystemComponent;

UCLASS()
class CARPENTER_API ACarpenterCharacter : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:

	ACarpenterCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//PROPERTY

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Input")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UContractSystemComponent> ContractSystemComponent;

	//METHOD

	void OnInteractAction(const FInputActionValue& InputActionValue);
	
};
