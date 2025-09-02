// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleOutButtonWidget.h"

#include "EnhancedInputComponent.h"
#include "Data/UIData/BattleOutButtonDataAsset.h"
#include "Managers/BgmManager.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"


UBattleOutButtonWidget::UBattleOutButtonWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBattleOutButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UBattleOutButtonDataAsset>(BaseDataAsset);
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		{
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				//Confirm
				if (UInputAction* InputActionConfirm = WidgetDataAsset->FindInputAction("Confirm"))
				{
					EnhancedInputComponent->BindAction(InputActionConfirm, ETriggerEvent::Started, this,
													   &UBattleOutButtonWidget::Input_ConfirmStarted);
				}
			}
		}
	}
}

void UBattleOutButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBattleOutButtonWidget::AddViewportEvent()
{
	Super::AddViewportEvent();

	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->AddTransitionWidget(this);
}

void UBattleOutButtonWidget::RemoveViewportEvent()
{
	this->RemoveFromParent();
}

void UBattleOutButtonWidget::Input_ConfirmStarted()
{
	if (ConfirmButtenAnim)
	{
		PlayAnimation(ConfirmButtenAnim);
		RemoveWidgetMappingContext();
	}
}

void UBattleOutButtonWidget::OnConfirmButtonEvent()
{                                                       
	FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Transition.BattleOutTransition");
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->AddViewportEvent();
}
