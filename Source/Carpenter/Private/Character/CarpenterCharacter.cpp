// Fill out your copyright notice in the Description page of Project Settings.


#include "Carpenter/Public/Character/CarpenterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Carpenter/DebugHelper.h"
#include "Framework/PlayerControllers/CarpenterPlayerController.h"

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
	if (!CachedCarpenterPlayerController)
	{
		CachedCarpenterPlayerController = CastChecked<ACarpenterPlayerController>(GetController());
	}

	if (TScriptInterface<IInteractable> InteractableObject = CachedCarpenterPlayerController->GetCurrentInteractableObject())
	{
		ServerRPC_InteractObject(InteractableObject, this);
		//InteractableObject->Interact(this);
	}
}

void ACarpenterCharacter::ServerRPC_InteractObject_Implementation(const TScriptInterface<IInteractable>& ObjectToInteract, APawn* InteractorPawn)
{
	if (ObjectToInteract)
	{
		ObjectToInteract->Interact(InteractorPawn);
	}
}
