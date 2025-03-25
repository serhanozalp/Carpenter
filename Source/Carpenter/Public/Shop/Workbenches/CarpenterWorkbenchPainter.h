// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buttons/CarpenterButton.h"
#include "Shop/CarpenterWorkbenchBase.h"
#include "CarpenterWorkbenchPainter.generated.h"

class ACarpenterItem;
class ACarpenterColorableButton;

UCLASS()
class CARPENTER_API ACarpenterWorkbenchPainter : public ACarpenterWorkbenchBase
{
	GENERATED_BODY()

public:

	ACarpenterWorkbenchPainter();
	
	virtual void Server_Initialize() override;

protected:

	virtual void BeginPlay() override;
	
	virtual void Server_BindWorkbenchButtonsDelegates() override;

private:

	//PROPERTY
	
	UPROPERTY(VisibleAnywhere, Category = "Custom|CarpenterWorkbenchPainter|Components")
	TObjectPtr<USceneComponent> PaintButtonsHolder;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterWorkbenchPainter|Components")
	TObjectPtr<UChildActorComponent> AttachButtonComponent;

	TArray<ACarpenterColorableButton*> PaintButtonList;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterWorkbenchPainter|Settings")
	float PaintButtonOffset = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|CarpenterWorkbenchPainter|Settings")
	TSubclassOf<ACarpenterColorableButton> PaintButtonClass;

	//METHOD

	void Server_GeneratePaintButtons();

	UFUNCTION()
	void Server_OnPaintButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);

	UFUNCTION()
	void Server_OnAttachButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);

	void Server_HandleCarpenterItemPaint(const FVector& ColorVectorToApply);
};
