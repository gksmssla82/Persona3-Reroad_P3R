// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseTransitionWidget.h"

UBaseTransitionWidget::UBaseTransitionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBaseTransitionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (TransitionAnim)
	{
		PlayAnimation(TransitionAnim);
	}
}
