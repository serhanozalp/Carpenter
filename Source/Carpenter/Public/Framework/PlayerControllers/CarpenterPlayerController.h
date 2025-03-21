// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarpenterPlayerController.generated.h"


class IInteractable;

UCLASS()
class CARPENTER_API ACarpenterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACarpenterPlayerController();
	virtual void Tick(float DeltaSeconds) override;

private:
	
	//PROPERTY

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Settings")
	float InteractionRange = 500.0f;

	UPROPERTY()
	TScriptInterface<IInteractable> CurrentInteractableObject;

	UPROPERTY()
	TScriptInterface<IInteractable> LastInteractableObject;
	
	//METHOD
	
	void CheckForInteractableActors();
	void HandleMouseTraceHitResult(const FHitResult& HitResult);
	void ResetInteractableObjects();
};
