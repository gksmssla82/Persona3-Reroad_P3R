// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyPanelFieldGroupWidget.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/VerticalBox.h"
#include "Data/UIData/PartyPanelFieldDataAsset.h"
#include "Data/UIData/PartyPanelFieldGroupDataAsset.h"
#include "System/BattleInstanceSubsystem.h"
#include "UI/PartyPanelFieldWidget.h"

UPartyPanelFieldGroupWidget::UPartyPanelFieldGroupWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),bIsPartyPanelSetting(false)
{
}

void UPartyPanelFieldGroupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UPartyPanelFieldGroupDataAsset>(BaseDataAsset);
	}
}

void UPartyPanelFieldGroupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPartyPanelFieldGroupWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (!bIsPartyPanelSetting)
	{
		Init_PartyPanelGroup();
		bIsPartyPanelSetting = true;
	}
	for (int32 i = 0; i < Group->GetChildrenCount(); i++)
	{
		if (UPartyPanelFieldWidget* MakePanel = Cast<UPartyPanelFieldWidget>(Group->GetChildAt(i)))
		{
			MakePanel->UpdateStatusBar();
		}
			
	}
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

void UPartyPanelFieldGroupWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	if (RemoveAnim)
	{
		PlayAnimation(RemoveAnim);
	}
}


void UPartyPanelFieldGroupWidget::Init_PartyPanelGroup()
{
	if (TArray<ATBC_PlayerBase*>* MakePlayerParty = &GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->
																		PlayerParty)
	{
		if (!MakePlayerParty->Num() == 0 && WidgetDataAsset)
		{
			int32 Index = 0;
			for (ATBC_PlayerBase* Iter : *(MakePlayerParty))
			{
				UPartyPanelFieldWidget* MakePartyPanel = CreateWidget<UPartyPanelFieldWidget>(
					this, WidgetDataAsset->GetPartyPanelFieldWidget());
				MakePartyPanel->Init_PartyPanelBattle(Iter);
				Group->AddChild(MakePartyPanel);
				Index++;
			}
		}
	}
}
