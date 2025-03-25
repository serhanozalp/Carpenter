// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ServerInitialize.h"
#include "CarpenterShopActorComponent.generated.h"


class ACarpenterShop;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARPENTER_API UCarpenterShopActorComponent : public UActorComponent, public IServerInitialize
{
	GENERATED_BODY()

public:
	
	UCarpenterShopActorComponent();
	virtual void Server_Initialize() override;

protected:

	//PROPERTY
	
	UPROPERTY()
	TObjectPtr<ACarpenterShop> CachedOwningCarpenterShop;

	//METHOD
	
	virtual void BeginPlay() override;
};
