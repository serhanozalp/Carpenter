// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ServerInitialize.h"
#include "CarpenterShop.generated.h"

class ACarpenterCharacter;
class ACarpenterItem;
class UResourceSystemComponent;
class UWidgetComponent;
class UContractSystemComponent;

UCLASS()
class CARPENTER_API ACarpenterShop : public AActor, public IServerInitialize
{
	GENERATED_BODY()

public:

	ACarpenterShop();
	FORCEINLINE UContractSystemComponent* GetContractSystemComponent() const { return ContractSystemComponent; }
	FORCEINLINE UResourceSystemComponent* GetResourceSystemComponent() const { return ResourceSystemComponent; }
	virtual void Server_Initialize() override;

protected:
	
	virtual void BeginPlay() override;

private:
	
	//PROPERTY

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere , Category = "Custom|Components")
	TObjectPtr<UStaticMeshComponent> ShopMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UContractSystemComponent> ContractSystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UResourceSystemComponent> ResourceSystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UWidgetComponent> AvailableContractsWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UWidgetComponent> ResourceWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UChildActorComponent> SellZone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> ChipperWorkbench;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> PainterWorkbench;

	//METHOD

	UFUNCTION()
	void Server_OnSellZoneButtonClicked(APawn* InteractorPawn);
};
