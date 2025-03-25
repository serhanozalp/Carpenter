// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ServerInitialize.h"
#include "CarpenterShop.generated.h"

class UDataAsset_ItemProperties;
class ACarpenterButton;
class ACarpenterCharacter;
class UResourceSystemComponent;
class UWidgetComponent;
class UContractSystemComponent;

UCLASS()
class CARPENTER_API ACarpenterShop : public AActor, public IServerInitialize
{
	GENERATED_BODY()

public:

	ACarpenterShop();
	
	virtual void Server_Initialize() override;
	
	FORCEINLINE UDataAsset_ItemProperties* GetItemPropertiesDataAsset() const { return ItemPropertiesDataAsset.Get(); };
	FORCEINLINE UResourceSystemComponent* GetResourceSystemComponent() const { return ResourceSystemComponent; }

protected:
	
	virtual void BeginPlay() override;

private:
	
	//PROPERTY

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere , Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UStaticMeshComponent> ShopMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UContractSystemComponent> ContractSystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UResourceSystemComponent> ResourceSystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UWidgetComponent> AvailableContractsWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UWidgetComponent> ResourceWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UChildActorComponent> SellButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UChildActorComponent> ChipperWorkbenchComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterShop|Components")
	TObjectPtr<UChildActorComponent> PainterWorkbenchComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterShop|Data")
	TSoftObjectPtr<UDataAsset_ItemProperties> ItemPropertiesDataAsset;

	//METHOD

	UFUNCTION()
	void Server_OnSellButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);
	void Server_LoadItemPropertiesDataAsset();
};
