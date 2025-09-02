// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AllOutAttackInputWidget.h"

#include "EnhancedInputComponent.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Data/UIData/AllOutAttackWidgetDataAsset.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"

UAllOutAttackInputWidget::UAllOutAttackInputWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UAllOutAttackInputWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UAllOutAttackWidgetDataAsset>(BaseDataAsset);
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
													   &UAllOutAttackInputWidget::Input_ConfirmStarted);
				}
			}
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				//Cancel
				if (UInputAction* InputActionCancel = WidgetDataAsset->FindInputAction("Cancel"))
				{
					EnhancedInputComponent->BindAction(InputActionCancel, ETriggerEvent::Started, this,
													   &UAllOutAttackInputWidget::Input_CancelStarted);
				}
			}
		}
	}
	
}

void UAllOutAttackInputWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAllOutAttackInputWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
	UE_LOG(LogTemp, Warning, TEXT("Add WidgetMappingContext"));
	
}

void UAllOutAttackInputWidget::RemoveViewportEvent()
{
	this->RemoveFromParent();
}

void UAllOutAttackInputWidget::Input_ConfirmStarted()
{
	if (ConfirmButtenAnim)
	{
		PlayAnimation(ConfirmButtenAnim);
		RemoveWidgetMappingContext();
	}
}

void UAllOutAttackInputWidget::Input_CancelStarted()
{
	if (CancelButtenAnim)
	{
		PlayAnimation(CancelButtenAnim);
		RemoveWidgetMappingContext();
	}
}

void UAllOutAttackInputWidget::OnConfirmButtenEvent()
{
	this->RemoveFromParent();
	
	//여기에 총공격 실행 코드 작성
	if (UBattleInstanceSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
	{
		for (auto& Player : Subsystem->PlayerParty)
		{
			Player->StatusComponent->SturnVfx_Off();
		}

		if (Subsystem->TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Makoto")
		{
			Subsystem->BattleCameraManager->Sequence_MainAllOut();
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle");
			GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->RemoveViewportEvent();
		}
		else if (Subsystem->TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Yukari")
		{
			Subsystem->BattleCameraManager->Sequence_YukariAllOut();
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle");
			GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->RemoveViewportEvent();
		}
		else if (Subsystem->TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Mitsuru")
		{
			Subsystem->BattleCameraManager->Sequence_MitsuruAllOut();
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle");
			GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->RemoveViewportEvent();
		}
		else
		{
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.ActionCommends");
			if (UBaseUIWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag))
			{
				GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->PushWidget(MakeWidget);
			}
		}
	}

	 
}

void UAllOutAttackInputWidget::OnCanCelButtenEvent()
{
	this->RemoveFromParent();
	//여기에 총공격 취소 코드 작성
	FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.ActionCommends");
	if (UBaseUIWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag))
	{
		GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->PushWidget(MakeWidget);
	}
}
