// Fill out your copyright notice in the Description page of Project Settings.


#include "Carpenter/Public/Character/CarpenterCharacter.h"

#include "CarpenterFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "CarpenterTypes/CarpenterEnumTypes.h"
#include "CarpenterTypes/CarpenterStructTypes.h"
#include "Components/Shop/ContractSystemComponent.h"
#include "Framework/PlayerControllers/CarpenterPlayerController.h"
#include "Shop/CarpenterWorkbenchBase.h"
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

void ACarpenterCharacter::Server_SetCarriedCarpenterItem(ACarpenterItem* CarpenterItem)
{
	if (!CarpenterItem)
	{
		CarriedCarpenterItem = nullptr;
		return;
	}
	
	if (IsCarryingCarpenterItem())
	{
		return;
	}
	
	CarriedCarpenterItem = CarpenterItem;
	CarriedCarpenterItem->AttachToComponent(PickedUpItemHolder, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CarriedCarpenterItem->Server_SetItemState(ECarpenterItemState::PickedUp);
	CarriedCarpenterItem->Server_SetAttachedWorkbench(nullptr);
}

float ACarpenterCharacter::Server_SellItem(UContractSystemComponent* ContractSystemComponent)
{
	if (!ContractSystemComponent || !IsCarryingCarpenterItem())
	{
		return 0.0f;
	}
	
	FCarpenterContractData ContractDataToCheck;
	ContractDataToCheck.RequestedItemData.Mesh = CarriedCarpenterItem->GetItemMesh();
	ContractDataToCheck.RequestedItemColor = UCarpenterFunctionLibrary::NativeConvertVectorToLinearColor(CarriedCarpenterItem->GetItemColorVector());
	
	if (CarriedCarpenterItem->Destroy())
	{
		CarriedCarpenterItem = nullptr;
	}
	
	return ContractSystemComponent->Server_CompleteContract(ContractDataToCheck);
}

void ACarpenterCharacter::ServerRPC_InteractObject_Implementation(const TScriptInterface<IInteractable>& ObjectToInteract, ACarpenterCharacter* InteractorCharacter)
{
	if (ObjectToInteract)
	{
		ObjectToInteract->Interact(InteractorCharacter);
	}
}
