// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseNamePlateWidget.h"

#include "Components/TextBlock.h"

UBaseNamePlateWidget::UBaseNamePlateWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBaseNamePlateWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void UBaseNamePlateWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UBaseNamePlateWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	PlayAnimation(CreateAnim);
}

void UBaseNamePlateWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

void UBaseNamePlateWidget::SetNamePlate(const FText& NewNamePlate)
{
	PlateTextBlock->SetText(NewNamePlate);
}

