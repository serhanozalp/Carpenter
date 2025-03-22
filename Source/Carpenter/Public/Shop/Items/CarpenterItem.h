// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CarpenterItem.generated.h"

UCLASS()
class CARPENTER_API ACarpenterItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	
	ACarpenterItem();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Interact(APawn* InteractorPawn) override;
	virtual void EnableOutline(bool bShouldEnable) override;

	void Server_SetItemMesh(UStaticMesh* InItemMesh);

private:

	//PROPERTY
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Materials")
	TObjectPtr<UMaterial> OverlayMaterial;

	UPROPERTY(ReplicatedUsing = OnRep_ItemMeshToApply)
	TObjectPtr<UStaticMesh> ItemMeshToApply;

	//METHOD

	UFUNCTION()
	void OnRep_ItemMeshToApply();
};
