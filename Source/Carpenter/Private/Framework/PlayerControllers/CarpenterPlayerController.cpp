// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PlayerControllers/CarpenterPlayerController.h"

#include "Interfaces/Interactable.h"

ACarpenterPlayerController::ACarpenterPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACarpenterPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckForInteractableActors();
}

void ACarpenterPlayerController::CheckForInteractableActors()
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn || !ControlledPawn->IsLocallyControlled() || !GetWorld())
	{
		return;
	}

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(ControlledPawn);
	
	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, CameraLocation + (CameraRotation.Vector() * InteractionRange), ECC_Visibility, QueryParams);
	HandleMouseTraceHitResult(HitResult);
}

void ACarpenterPlayerController::HandleMouseTraceHitResult(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
	{
		ResetInteractableObjects();
		return;
	}
	
	if (HitActor->Implements<UInteractable>())
	{
		TScriptInterface<IInteractable> NewInteractableObject = HitActor;
		if (NewInteractableObject == CurrentInteractableObject)
		{
			return;
		}
		CurrentInteractableObject = NewInteractableObject;
		CurrentInteractableObject->EnableOutline(true);
		if (LastInteractableObject && LastInteractableObject != CurrentInteractableObject)
		{
			LastInteractableObject->EnableOutline(false);
		}
		LastInteractableObject = CurrentInteractableObject;
	}
	else
	{
		ResetInteractableObjects();
	}
}

void ACarpenterPlayerController::ResetInteractableObjects()
{
	if (LastInteractableObject)
	{
		LastInteractableObject->EnableOutline(false);
		LastInteractableObject = nullptr;
	}
	if (CurrentInteractableObject)
	{
		CurrentInteractableObject->EnableOutline(false);
		CurrentInteractableObject = nullptr;
	}
}
