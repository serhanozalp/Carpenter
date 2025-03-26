// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carpenter/TP_FirstPerson/TP_FirstPersonCharacter.h"
#include "Interfaces/Interactable.h"
#include "CarpenterCharacter.generated.h"

class ACarpenterWorkbenchBase;
class ACarpenterItem;
class ACarpenterPlayerController;
class UContractSystemComponent;

UCLASS()
class CARPENTER_API ACarpenterCharacter : public ATP_FirstPersonCharacter
{
	GENERATED_BODY()

public:

	ACarpenterCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Server_SetCarriedCarpenterItem(ACarpenterItem* CarpenterItem);
	float Server_SellItem(UContractSystemComponent* ContractSystemComponent);
	
	FORCEINLINE ACarpenterItem* GetCarriedCarpenterItem() const { return CarriedCarpenterItem; }

private:

	//PROPERTY

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterCharacter|Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterCharacter|Components")
	TObjectPtr<USceneComponent> PickedUpItemHolder;
	
	UPROPERTY()
	TObjectPtr<ACarpenterPlayerController> CachedCarpenterPlayerController;

	UPROPERTY()
	TObjectPtr<ACarpenterItem> CarriedCarpenterItem;

	//METHOD

	bool IsCarryingCarpenterItem() const { return CarriedCarpenterItem != nullptr; }
	
	void OnInteractAction(const FInputActionValue& InputActionValue);
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_InteractObject(const TScriptInterface<IInteractable>& ObjectToInteract, ACarpenterCharacter* InteractorCharacter);
};
