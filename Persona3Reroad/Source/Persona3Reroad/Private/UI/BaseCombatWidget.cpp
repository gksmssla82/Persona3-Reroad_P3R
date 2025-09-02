// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseCombatWidget.h"

UBaseCombatWidget::UBaseCombatWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBaseCombatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseCombatWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseCombatWidget::PlayCombatAnimation()
{
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}
