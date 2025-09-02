// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CombatDamageFontUIWidget.h"

#include "Data/UIData/CombatDamageFontDataAsset.h"

UCombatDamageFontUIWidget::UCombatDamageFontUIWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UCombatDamageFontUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UCombatDamageFontDataAsset>(BaseDataAsset);
	}
	Damage2D = FUImage2D(Damage,DamageBak);
}

void UCombatDamageFontUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayDamageFontAnimation(ECombatDamageFontAnimType::Reset);
}

void UCombatDamageFontUIWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
}

void UCombatDamageFontUIWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

void UCombatDamageFontUIWidget::Init_DamageFont(int32 InNumber, bool Weak)
{
	if (WidgetDataAsset)
	{
		if (FSprite2D* MakeSprite2D =  WidgetDataAsset->GetDamageFontSprite2D(InNumber))
		{
			Damage2D.SetMemberFromSprite2D(MakeSprite2D);
		}
		if (Weak)
		{
			if (FLinearColor* MakeColor = WidgetDataAsset->FindDamageFontColor("Weak"))
			{
				DamageBak->SetBrushTintColor(*MakeColor);
				
			}
		}
		else
		{
			if (FLinearColor* MakeColor = WidgetDataAsset->FindDamageFontColor("Default"))
			{
				DamageBak->SetBrushTintColor(*MakeColor);
				//UE_LOG(LogTemp,Warning,TEXT("안약점"));
			}
		}
	}
	
}

void UCombatDamageFontUIWidget::PlayDamageFontAnimation(ECombatDamageFontAnimType AnimType)
{

	switch (AnimType) {
	case ECombatDamageFontAnimType::Create:
		if (CreateAnim)
		{
			PlayAnimation(CreateAnim);
		}
		break;
	case ECombatDamageFontAnimType::Reset:
		if (Reset)
		{
			PlayAnimation(Reset);
		}
		break;
	default:
		break;
	}

}

void UCombatDamageFontUIWidget::SetDamageBakColor()
{
}
