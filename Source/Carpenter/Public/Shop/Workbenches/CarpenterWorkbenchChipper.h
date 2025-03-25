// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shop/CarpenterWorkbenchBase.h"
#include "CarpenterWorkbenchChipper.generated.h"

class ACarpenterButton;
class ACarpenterItem;
class UCarpenterWidgetChipperDisplay;
struct FCarpenterItemData;
class UWidgetComponent;

UCLASS()
class CARPENTER_API ACarpenterWorkbenchChipper : public ACarpenterWorkbenchBase
{
	GENERATED_BODY()

public:

	ACarpenterWorkbenchChipper();
	virtual void Server_Initialize() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void Server_BindWorkbenchButtonsDelegates() override;
	
private:

	//PROPERTY

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UChildActorComponent> LeftButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UChildActorComponent> RightButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UChildActorComponent> BuildButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UWidgetComponent> ItemDisplayWidgetComponent;

	UPROPERTY(Replicated)
	TArray<FCarpenterItemData> CarpenterItemDataList;

	UPROPERTY(ReplicatedUsing = OnRep_SelectedItemIndex)
	int32 SelectedItemIndex;

	TObjectPtr<UCarpenterWidgetChipperDisplay> CachedItemDisplayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Settings")
	TSubclassOf<ACarpenterItem> CarpenterItemClass;

	//METHOD

	UFUNCTION()
	void OnRep_SelectedItemIndex();
	
	void Server_SetSelectedItemIndex(int32 NewItemIndex);

	void HandleItemDisplayWidget();

	UFUNCTION()
	void Server_OnLeftButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);
	
	UFUNCTION()
	void Server_OnRightButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);

	UFUNCTION()
	void Server_OnBuildButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton);

	void Server_HandleItemBuild();
};
