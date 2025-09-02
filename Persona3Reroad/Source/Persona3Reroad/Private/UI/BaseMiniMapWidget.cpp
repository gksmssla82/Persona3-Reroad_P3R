// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseMiniMapWidget.h"

UBaseMiniMapWidget::UBaseMiniMapWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UBaseMiniMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseMiniMapWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseMiniMapWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (ScreenIn)
	{
		PlayAnimation(ScreenIn);
	}
	
}

void UBaseMiniMapWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	if (ScreenOut)
	{
		PlayAnimation(ScreenOut);
	}
}




