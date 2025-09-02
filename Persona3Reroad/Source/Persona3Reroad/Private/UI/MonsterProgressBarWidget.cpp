// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MonsterProgressBarWidget.h"

#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Components/TurnComponent.h"
#include "Data/UIData/MonsterProgressBarDataAsset.h"
#include "System/BattleInstanceSubsystem.h"

UMonsterProgressBarWidget::UMonsterProgressBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UMonsterProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UMonsterProgressBarDataAsset>(BaseDataAsset);
	}
}

void UMonsterProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMonsterProgressBarWidget::Init_ProgressBar(const TObjectPtr<ATBC_CharacterBase>& InOwner)
{
	Super::Init_ProgressBar(InOwner);
	
}

void UMonsterProgressBarWidget::SetElementType(EElement InElement)
{
	if (UPaperSprite* MakeSprite =  WidgetDataAsset->FindElementImage(InElement))
	{
		AttackType->SetBrushResourceObject(MakeSprite);
	}
}
		

