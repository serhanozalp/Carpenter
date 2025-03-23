// Fill out your copyright notice in the Description page of Project Settings.


#include "Carpenter/Public/Character/CarpenterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Carpenter/DebugHelper.h"
#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/ContractSystemComponent.h"
#include "Framework/PlayerControllers/CarpenterPlayerController.h"
#include "Shop/Items/CarpenterItem.h"

ACarpenterCharacter::ACarpenterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PickedUpItemHolder = CreateDefaultSubobject<USceneComponent>(TEXT("PickedUp Item Holder"));
	PickedUpItemHolder->SetupAttachment(GetRootComponent());
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
	}
}

bool ACarpenterCharacter::Server_PickupItem(ACarpenterItem* ItemToPickUp)
{
	if (!ItemToPickUp || CarriedCarpenterItem)
	{
		return false;
	}

	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	if (ItemToPickUp->AttachToComponent(PickedUpItemHolder, TransformRules))
	{
		CarriedCarpenterItem = ItemToPickUp;
		return true;
	}
	return false;
}

float ACarpenterCharacter::Server_SellItem(UContractSystemComponent* ContractSystemComponent)
{
	if (!ContractSystemComponent || !CarriedCarpenterItem)
	{
		return 0.0f;
	}
	
	FCarpenterContractData ContractDataToCheck;
	ContractDataToCheck.RequestedItemData.Mesh = CarriedCarpenterItem->GetItemMesh();
	
	if (CarriedCarpenterItem->Destroy())
	{
		CarriedCarpenterItem = nullptr;
	}
	
	return ContractSystemComponent->Server_CompleteContract(ContractDataToCheck);
}

void ACarpenterCharacter::ServerRPC_InteractObject_Implementation(const TScriptInterface<IInteractable>& ObjectToInteract, APawn* InteractorPawn)
{
	if (ObjectToInteract)
	{
		ObjectToInteract->Interact(InteractorPawn);
	}
}
