// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CombatDamageGroupWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Data/UIData/CombatDamageGroupDataAsset.h"

UCombatDamageGroupWidget::UCombatDamageGroupWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UCombatDamageGroupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UCombatDamageGroupDataAsset>(BaseDataAsset);
	}
}

void UCombatDamageGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCombatDamageGroupWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
}

void UCombatDamageGroupWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

void UCombatDamageGroupWidget::Init_CombatDamageGroup(const int32& InDamage, const bool& bIsWeak)
{
	TArray<int32> MakeNumArray = SplitNumberIntoDigits(InDamage);

	HorizontalDamageBox->ClearChildren();
	for (int32 i = 0; i < MakeNumArray.Num(); i++)
	{
		if (WidgetDataAsset)
		{
			if (TSubclassOf<UCombatDamageFontUIWidget> MakeDamageFontClass =  WidgetDataAsset->GetDamageFontClass())
			{
				if (UUserWidget* MakeUserWidget = CreateWidget(this,MakeDamageFontClass))
				{
					if (UCombatDamageFontUIWidget* MakeDamageFont = Cast<UCombatDamageFontUIWidget>(MakeUserWidget))
					{
						MakeDamageFont->Init_DamageFont(MakeNumArray[i],bIsWeak);
						HorizontalDamageBox->InsertChildAt(0,MakeDamageFont);

						if(UHorizontalBoxSlot* MakeSlot = Cast<UHorizontalBoxSlot>(HorizontalDamageBox->GetChildAt(0)->Slot))
						{
							MakeSlot->SetPadding(FMargin(0.0f,0.0f,-55.0f,0.0f));
						}
					}
				}
			}
		}
	}
	PlayDamageGroupAnimation();
}

void UCombatDamageGroupWidget::PlayDamageGroupAnimation()
{
	int32 Num = 0;
	
	
	for (int32 i  = 0; i < HorizontalDamageBox->GetChildrenCount(); i++)
	{
		if (UCombatDamageFontUIWidget* MakeDamageFont = Cast<UCombatDamageFontUIWidget>(HorizontalDamageBox->GetChildAt(i)))
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,
												   [MakeDamageFont]()
												   {
												   	MakeDamageFont->PlayDamageFontAnimation(ECombatDamageFontAnimType::Create);
												   },
												   0.01f + 0.07f * i,
												   false);
		}
		Num++;
	}
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,
												   [this]()
												   {
													   if (Reset)
													   {
														   this->PlayAnimation(Reset);
													   }
												   },
												   0.4f + 0.07f * Num,
												   false);
}
