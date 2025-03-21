// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarpenterWorkbenchBase.generated.h"


UCLASS()
class CARPENTER_API ACarpenterWorkbenchBase : public AActor
{
	GENERATED_BODY()

public:
	
	ACarpenterWorkbenchBase();

private:

	UPROPERTY(VisibleAnywhere, Category = "Custom|Components")
	TObjectPtr<UStaticMeshComponent> WorkbenchMesh;
};
