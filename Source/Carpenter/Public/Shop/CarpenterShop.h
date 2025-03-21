// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarpenterShop.generated.h"

class UWidgetComponent;
class UContractSystemComponent;

UCLASS()
class CARPENTER_API ACarpenterShop : public AActor
{
	GENERATED_BODY()

public:

	ACarpenterShop();
	FORCEINLINE UContractSystemComponent* GetContractSystemComponent() const { return ContractSystemComponent; }

protected:
	
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ShopMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UContractSystemComponent> ContractSystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> AvailableContractsWidget;
};
