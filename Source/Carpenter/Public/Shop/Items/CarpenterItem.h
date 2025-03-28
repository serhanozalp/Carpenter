﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CarpenterItem.generated.h"

class ACarpenterWorkbenchBase;
enum class ECarpenterItemState : uint8;
class ACarpenterCharacter;

UCLASS()
class CARPENTER_API ACarpenterItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	
	ACarpenterItem();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Interact(ACarpenterCharacter* InteractorCharacter) override;
	virtual void EnableOutline(bool bShouldEnable) override;
	
	void Server_SetItemMesh(UStaticMesh* ItemMesh);
	void Server_SetItemColor(const FVector& ColorVector);
	void Server_SetItemState(ECarpenterItemState InItemState);
	void Server_SetAttachedWorkbench(ACarpenterWorkbenchBase* Workbench);
	
	FORCEINLINE UStaticMesh* GetItemMesh() const { return ItemMeshComponent->GetStaticMesh(); }
	FORCEINLINE FVector GetItemColorVector() const { return ColorVectorToApply; }

private:

	//PROPERTY
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterItem|Components")
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterItem|Materials")
	TObjectPtr<UMaterial> OverlayMaterial;

	UPROPERTY()
	TObjectPtr<ACarpenterWorkbenchBase> AttachedWorkBench;

	UPROPERTY(ReplicatedUsing = OnRep_ItemMeshToApply)
	TObjectPtr<UStaticMesh> ItemMeshToApply;

	UPROPERTY(ReplicatedUsing = OnRep_ColorVectorToApply)
	FVector ColorVectorToApply;

	UPROPERTY(ReplicatedUsing = OnRep_ItemState)
	ECarpenterItemState ItemState;

	//METHOD

	UFUNCTION()
	void OnRep_ItemMeshToApply();

	UFUNCTION()
	void OnRep_ColorVectorToApply();
	
	UFUNCTION()
	void OnRep_ItemState();

	void HandleItemState();
};
