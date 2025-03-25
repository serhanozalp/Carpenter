// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop/Workbenches/CarpenterWorkbenchPainter.h"

#include "Carpenter/DebugHelper.h"
#include "Character/CarpenterCharacter.h"
#include "DataAssets/DataAsset_ItemProperties.h"
#include "Shop/CarpenterShop.h"
#include "Shop/Items/CarpenterItem.h"
#include "Shop/Workbenches/Buttons/CarpenterColorableButton.h"

ACarpenterWorkbenchPainter::ACarpenterWorkbenchPainter()
{
	PrimaryActorTick.bCanEverTick = true;

	PaintButtonsHolder = CreateDefaultSubobject<USceneComponent>("Paint Buttons Holder");
	PaintButtonsHolder->SetupAttachment(GetRootComponent());

	AttachButtonComponent = CreateDefaultSubobject<UChildActorComponent>("Attach Button Component");
	AttachButtonComponent->SetupAttachment(GetRootComponent());
}

void ACarpenterWorkbenchPainter::Server_Initialize() 
{
	Server_GeneratePaintButtons();
	Server_BindWorkbenchButtonsDelegates();
}

void ACarpenterWorkbenchPainter::Server_BindWorkbenchButtonsDelegates()
{
	if (AActor* ChildActor = AttachButtonComponent->GetChildActor())
	{
		if (ACarpenterButton* AttachButton = Cast<ACarpenterButton>(ChildActor))
		{
			AttachButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchPainter::Server_OnAttachButtonClicked);
		}
	}
	for (ACarpenterColorableButton* PaintButton : PaintButtonList)
	{
		PaintButton->OnButtonInteracted.AddDynamic(this, &ACarpenterWorkbenchPainter::Server_OnPaintButtonClicked);
	}
}

void ACarpenterWorkbenchPainter::Server_GeneratePaintButtons()
{
	if (!OwningCarpenterShop || !GetWorld())
	{
		return;
	}
	
	UDataAsset_ItemProperties* ItemPropertiesDataAsset = OwningCarpenterShop->GetItemPropertiesDataAsset();
	
	for (int i = 0; i < ItemPropertiesDataAsset->ColorList.Num(); ++i)
	{
		ACarpenterColorableButton* PaintButton = GetWorld()->SpawnActor<ACarpenterColorableButton>(PaintButtonClass, FVector::ZeroVector, FRotator::ZeroRotator);
		PaintButtonList.Add(PaintButton);
		
		PaintButton->AttachToComponent(PaintButtonsHolder, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PaintButton->SetActorRelativeLocation(FVector(i * PaintButtonOffset, 0.0f, 0.0f));
		
		FLinearColor Color = ItemPropertiesDataAsset->ColorList[i];
		FVector ColorVector(Color.R, Color.G, Color.B);
		PaintButton->Server_SetColorVectorToApply(ColorVector);
	}
}

void ACarpenterWorkbenchPainter::Server_OnPaintButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
}

void ACarpenterWorkbenchPainter::Server_OnAttachButtonClicked(ACarpenterCharacter* InteractorCharacter, ACarpenterButton* InteractedButton)
{
	if (!InteractorCharacter || !InteractorCharacter->GetCarriedCarpenterItem() || !IsEmpty())
	{
		return;
	}
	
	Server_SetAttachedCarpenterItem(InteractorCharacter->GetCarriedCarpenterItem());
	InteractorCharacter->Server_SetCarriedCarpenterItem(nullptr);
}

