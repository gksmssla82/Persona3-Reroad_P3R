// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseFloatingWidget.h"

UBaseFloatingWidget::UBaseFloatingWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBaseFloatingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseFloatingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Reset)
	{
		PlayAnimation(Reset);
	}
}

void UBaseFloatingWidget::PlayFloatingAnimation()
{
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

