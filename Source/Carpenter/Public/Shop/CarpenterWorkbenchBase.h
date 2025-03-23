// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ServerInitialize.h"
#include "CarpenterWorkbenchBase.generated.h"

class ACarpenterShop;

UCLASS()
class CARPENTER_API ACarpenterWorkbenchBase : public AActor, public IServerInitialize
{
	GENERATED_BODY()

public:
	
	ACarpenterWorkbenchBase();
	virtual void Server_Initialize() override;

	void Server_SetIsEmpty(bool bInIsEmpty);

protected:

	//PROPERTY
	
	UPROPERTY()
	TObjectPtr<ACarpenterShop> OwningCarpenterShop;

	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<USceneComponent> ItemHolderComponent;

	bool bIsEmpty = true;

	//METHOD
	
	UFUNCTION(BlueprintCallable, DisplayName = "Set Owning Shop")
	void SetOwningCarpenterShop(ACarpenterShop* CarpenterShop);

private:

	//PROPERTY

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UStaticMeshComponent> WorkbenchMesh;
};
