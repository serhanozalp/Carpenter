// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shop/CarpenterWorkbenchBase.h"
#include "CarpenterWorkbenchChipper.generated.h"

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
	
private:

	//PROPERTY

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftButtonComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightButtonComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> BuildButtonComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UWidgetComponent> ItemDisplayWidgetComponent;

	UPROPERTY(Replicated)
	TArray<FCarpenterItemData> CarpenterItemDataList;

	UPROPERTY(ReplicatedUsing = OnRep_SelectedItemIndex)
	int32 SelectedItemIndex;

	TObjectPtr<UCarpenterWidgetChipperDisplay> ItemDisplayWidget;

	//METHOD

	UFUNCTION()
	void OnRep_SelectedItemIndex();
	
	void Server_SetSelectedItemIndex(int32 ItemIndex);

	UFUNCTION(Server, Reliable)
	void ServerRPC_LeftButtonClicked();

	UFUNCTION(Server, Reliable)
	void ServerRPC_RightButtonClicked();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BuildButtonClicked();

	void HandleItemDisplayWidget();
	
	UFUNCTION()
	void OnRightButtonClicked();

	UFUNCTION()
	void OnLeftButtonClicked();

	UFUNCTION()
	void OnBuildButtonClicked();
	
	void BindButtonDelegates();
};
