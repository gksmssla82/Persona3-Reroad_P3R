// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BasePartyPanelWidget.h"

#include "Components/ProgressBar.h"

UBasePartyPanelWidget::UBasePartyPanelWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UBasePartyPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBasePartyPanelWidget::SetHPBarPercent(const float MaxHP, const float CurrentHP)
{
	if (HPBar)
	{
		HPBar->SetPercent(NormalizeProgressBarPercent(MaxHP, CurrentHP));
	}
}

void UBasePartyPanelWidget::SetSPBarPercent(const float MaxSP, const float CurrentSP)
{
	if (SPBar)
	{
		SPBar->SetPercent(NormalizeProgressBarPercent(MaxSP, CurrentSP));
	}
}
