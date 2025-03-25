// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ServerInitialize.h"
#include "CarpenterWorkbenchBase.generated.h"

class ACarpenterItem;
class ACarpenterShop;

UCLASS()
class CARPENTER_API ACarpenterWorkbenchBase : public AActor, public IServerInitialize
{
	GENERATED_BODY()

public:
	
	ACarpenterWorkbenchBase();
	
	virtual void Server_Initialize() override;
	void Server_SetAttachedCarpenterItem(ACarpenterItem* CarpenterItemToAttach);

	void SetOwningCarpenterShop(ACarpenterShop* CarpenterShop);
	
protected:

	//PROPERTY
	
	UPROPERTY()
	TObjectPtr<ACarpenterShop> OwningCarpenterShop;

	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterWorkbenchBase|Components")
	TObjectPtr<USceneComponent> ItemHolderComponent;

	UPROPERTY()
	TObjectPtr<ACarpenterItem> AttachedCarpenterItem;

	//METHOD
	
	

	virtual void Server_BindWorkbenchButtonsDelegates();

	bool IsEmpty() const { return AttachedCarpenterItem == nullptr; }

private:

	//PROPERTY

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterWorkbenchBase|Components")
	TObjectPtr<UStaticMeshComponent> WorkbenchMesh;
};
