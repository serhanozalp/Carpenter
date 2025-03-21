// Fill out your copyright notice in the Description page of Project Settings.


#include "Carpenter/Public/Character/CarpenterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/ContractSystemComponent.h"

ACarpenterCharacter::ACarpenterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ACarpenterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACarpenterCharacter::OnInteractAction);
	}
}

void ACarpenterCharacter::OnInteractAction(const FInputActionValue& InputActionValue)
{
}
