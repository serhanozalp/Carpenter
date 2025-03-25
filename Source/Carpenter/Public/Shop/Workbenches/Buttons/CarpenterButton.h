// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CarpenterButton.generated.h"

class ACarpenterWorkbenchBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonInteracted, ACarpenterCharacter*, InteractorCharacter, ACarpenterButton*, InteractedButton);

UCLASS()
class CARPENTER_API ACarpenterButton : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	//PROPERTY

	FOnButtonInteracted OnButtonInteracted;
	
	//METHOD
	
	ACarpenterButton();
	virtual void Interact(ACarpenterCharacter* InteractorCharacter) override;
	virtual void EnableOutline(bool bShouldEnable) override;

protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Materials")
	TObjectPtr<UMaterial> OverlayMaterial;
};
