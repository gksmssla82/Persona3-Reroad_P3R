// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DayWidget.h"

UDayWidget::UDayWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UDayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UDayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDayWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

void UDayWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	if (RemoveAnim)
	{
		PlayAnimation(RemoveAnim);
	}
}
