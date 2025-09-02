// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BasePartyPanelGroupWidget.h"

#include "Components/VerticalBox.h"

UBasePartyPanelGroupWidget::UBasePartyPanelGroupWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBasePartyPanelGroupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBasePartyPanelGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBasePartyPanelGroupWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
}

void UBasePartyPanelGroupWidget::AddViewportEvent(const int32& InZOrder)
{
	Super::AddViewportEvent(InZOrder);
}

void UBasePartyPanelGroupWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

UBaseUIWidget* UBasePartyPanelGroupWidget::FindPanelWidget(const FName& InName)
{
	return nullptr;
}

void UBasePartyPanelGroupWidget::PlayGroupAnimation()
{
}

