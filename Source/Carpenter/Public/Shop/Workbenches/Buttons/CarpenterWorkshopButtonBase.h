// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CarpenterWorkshopButtonBase.generated.h"

class ACarpenterWorkbenchBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonInteracted);

UCLASS()
class CARPENTER_API ACarpenterWorkshopButtonBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	//PROPERTY
	UPROPERTY(BlueprintAssignable, Category = "Custom|Delegates")
	FOnButtonInteracted OnButtonInteracted;
	
	//METHOD
	
	ACarpenterWorkshopButtonBase();
	virtual void Interact(APawn* InteractorPawn) override;
	virtual void EnableOutline(bool bShouldEnable) override;

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Materials")
	TObjectPtr<UMaterial> OverlayMaterial;
};
