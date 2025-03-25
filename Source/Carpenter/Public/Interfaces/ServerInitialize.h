// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ServerInitialize.generated.h"

UINTERFACE()
class UServerInitialize : public UInterface
{
	GENERATED_BODY()
};

class CARPENTER_API IServerInitialize
{
	GENERATED_BODY()
	
public:
	
	virtual void Server_Initialize() = 0;
};
