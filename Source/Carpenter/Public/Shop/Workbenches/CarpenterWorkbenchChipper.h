// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shop/CarpenterWorkbenchBase.h"
#include "CarpenterWorkbenchChipper.generated.h"

class UWidgetComponent;

UCLASS()
class CARPENTER_API ACarpenterWorkbenchChipper : public ACarpenterWorkbenchBase
{
	GENERATED_BODY()

public:

	ACarpenterWorkbenchChipper();
	virtual void Server_Initialize() override;
	
protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Custom|Events")
	void LeftButtonClicked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Custom|Events")
	void RightButtonClicked();
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Components")
	TObjectPtr<UWidgetComponent> ItemDisplayWidget;
};
