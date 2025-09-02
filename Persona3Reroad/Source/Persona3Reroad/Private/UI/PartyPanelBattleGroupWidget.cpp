// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyPanelBattleGroupWidget.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/UIData/PartyPanelBattleGroupDataAsset.h"
#include "System/BattleInstanceSubsystem.h"
#include "UI/PartyPanelBattleWidget.h"

UPartyPanelBattleGroupWidget::UPartyPanelBattleGroupWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),bIsPartyPanelSetting(false)
{
}

void UPartyPanelBattleGroupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UPartyPanelBattleGroupDataAsset>(BaseDataAsset);
	}
}

void UPartyPanelBattleGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPartyPanelBattleGroupWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (Group->GetChildrenCount() <=0)
	{
		Init_PartyPanelGroup();
	}
	PlayGroupAnimation();
	
}

void UPartyPanelBattleGroupWidget::AddViewportEvent(const int32& InZOrder)
{
	Super::AddViewportEvent(InZOrder);
	if (!bIsPartyPanelSetting)
	{
		Init_PartyPanelGroup();
		bIsPartyPanelSetting = true;
	}
	PlayGroupAnimation();
}

void UPartyPanelBattleGroupWidget::RemoveViewportEvent()
{
	if (bIsPartyPanelSetting)
	{
		for (int i = 0; i < Group->GetChildrenCount(); i++)
		{
			if (USizeBox* MakeSizeBox = Cast<USizeBox>(Group->GetChildAt(i)))
			{
				if (UPartyPanelBattleWidget* MakePanel = Cast<UPartyPanelBattleWidget>(MakeSizeBox->GetChildAt(0)))
				{
					MakePanel->PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType::Hidden);
				}
			}
		}
	}
	//Super::RemoveViewportEvent();
}

void UPartyPanelBattleGroupWidget::PlayGroupAnimation()
{
	Super::PlayGroupAnimation();
	for (int32 i = 0; i < Group->GetChildrenCount(); i++)
	{
		if (USizeBox* MakeWidget = Cast<USizeBox>(Group->GetChildAt(i)))
		{
			if (UPartyPanelBattleWidget* MakePartyPanel = Cast<UPartyPanelBattleWidget>(MakeWidget->GetChildAt(0)))
			{
				
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,
			                                       [MakePartyPanel]()
			                                       {
				                                       MakePartyPanel->PlayPartyPanelBattleAnim(
					                                       EPartyPanelBattleAnimType::Create);
			                                       },
			                                       0.01f + 0.06f * i,
			                                       false);
			}
		}
	}
}


void UPartyPanelBattleGroupWidget::Init_PartyPanelGroup()
{
	if (TArray<ATBC_PlayerBase*>* MakePlayerParty = &GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->
	                                                                    PlayerParty)
	{
		if (!MakePlayerParty->Num() == 0 && WidgetDataAsset)
		{
			int32 Index = 0;
			for (ATBC_PlayerBase* Iter : *(MakePlayerParty))
			{
				UPartyPanelBattleWidget* MakePartyPanel = CreateWidget<UPartyPanelBattleWidget>(
					this, WidgetDataAsset->GetPartyPanelBattleWidget());
				MakePartyPanel->Init_PartyPanelBattle(Iter);
				
				if (USizeBox* MakePanel = Cast<USizeBox>(Group->GetChildAt(Index)))
				{
					MakePanel->AddChild(MakePartyPanel);
				}
				Index++;
			}
			for (int i = 0; i < Group->GetChildrenCount(); i++)
			{
				if (UPartyPanelBattleWidget* MakeWidget = Cast<UPartyPanelBattleWidget>(Group->GetChildAt(i)))
				{
					UVerticalBoxSlot* MakeSlot = Cast<UVerticalBoxSlot>(MakeWidget->Slot);
					MakeSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
					MakeSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, -20.0f));
				}
			}
		}
	}
}
