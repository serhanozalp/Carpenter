﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CARPENTER_API IInteractable
{
	GENERATED_BODY()
	
public:

	virtual void Interact(APawn* InteractorPawn) = 0;
	virtual void EnableOutline(bool bShouldEnable) = 0;
};
