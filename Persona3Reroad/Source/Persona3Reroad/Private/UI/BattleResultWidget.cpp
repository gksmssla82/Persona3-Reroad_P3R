// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleResultWidget.h"

#include "System/WidgetInstanceSubsystem.h"


UBattleResultWidget::UBattleResultWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBattleResultWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattleResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBattleResultWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->AddTransitionWidget(this);
}

void UBattleResultWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}
