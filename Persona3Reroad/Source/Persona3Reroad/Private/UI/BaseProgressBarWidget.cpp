// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseProgressBarWidget.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/TurnComponent.h"
#include "Data/UIData/BaseProgressBarDataAsset.h"
#include "System/BattleInstanceSubsystem.h"
#include "UI/BaseFloatingWidget.h"
#include "UI/CombatDamageGroupWidget.h"
#include "UI/MonsterProgressBarWidget.h"

UBaseProgressBarWidget::UBaseProgressBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),bIsWeak(false)
{
}

void UBaseProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (BaseDataAsset)
	{
		BaseWidgetDataAsset = Cast<UBaseProgressBarDataAsset>(BaseDataAsset);
	}
}

void UBaseProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayProgressAnimation(EProgressBarAnimType::Reset);
}

void UBaseProgressBarWidget::Init_ProgressBar(const TObjectPtr<ATBC_CharacterBase>& InOwner)
{
	if (InOwner)
	{
		WidgetOwner = InOwner;

		//Bind Delegate
		WidgetOwner->StatusComponent->OnHitDeleGateThreeParam.AddDynamic(this, &UBaseProgressBarWidget::OnHitEvent);
		
		WidgetOwner->StatusComponent->OnWeakDeleGate.AddDynamic(this, &UBaseProgressBarWidget::OnWeakEvent);
		WidgetOwner->StatusComponent->OnCriticalDeleGate.AddDynamic(this, &UBaseProgressBarWidget::OnCriticalEvent);
		WidgetOwner->StatusComponent->OnResistDeleGate.AddDynamic(this, &UBaseProgressBarWidget::OnResistEvent);
		WidgetOwner->StatusComponent->OnMissDeleGate.AddDynamic(this, &UBaseProgressBarWidget::OnMissEvent);
		

		//이건수정좀해야할듯?
		GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->ReadyNextTurnWidgetDelegate.AddDynamic(this, &UBaseProgressBarWidget::OnTurnEndEvent);
		
	UpdateHPBar();
	UpdateHPBarRate();
	}
	
}

void UBaseProgressBarWidget::PlayProgressAnimation(EProgressBarAnimType InProgressBarAnimType)
{
	switch (InProgressBarAnimType)
	{
	case EProgressBarAnimType::Reset:
		if (Reset)
		{
			PlayAnimation(Reset);
			UpdateHPBarRate();
		}
		break;
	case EProgressBarAnimType::Create:
		if (Reset)
		{
			StopAnimation(Reset);
		}
		if (CreateAnim)
		{
			PlayAnimation(CreateAnim);
		}
		break;
	case EProgressBarAnimType::Hit:
		if (HitAnim)
		{
			PlayAnimation(HitAnim);
		}
		break;
	default:
		break;
	}
}


void UBaseProgressBarWidget::OnHitEvent(int32 Damage)
{
	PlayProgressAnimation(EProgressBarAnimType::Hit);
	UpdateHPBar();

	if (BaseWidgetDataAsset)
	{
		if (TSubclassOf<UCombatDamageGroupWidget> MakeSubClass = BaseWidgetDataAsset->GetCombatDamageGroup())
		{
			if (UUserWidget* MakeWidget = CreateWidget(this, MakeSubClass))
			{
				if (UCombatDamageGroupWidget* MakeDamage = Cast<UCombatDamageGroupWidget>(MakeWidget))
				{
					MakeDamage->Init_CombatDamageGroup(Damage, bIsWeak);
					RootDamageGroup->AddChildToCanvas(MakeDamage);
					bIsWeak = false;

					if (RootDamageGroup->GetChildAt(RootDamageGroup->GetChildrenCount() - 1))
					{
						if (UCanvasPanelSlot* MakePanel = Cast<UCanvasPanelSlot>(
							RootDamageGroup->GetChildAt(RootDamageGroup->GetChildrenCount() - 1)->Slot))
						{
							MakePanel->SetAnchors(FAnchors(0.5f,0.5f));
							MakePanel->SetAlignment(FVector2D(0.5f,0.5f));
							MakePanel->SetAutoSize(true);

							int32 RandX = FMath::RandRange(-40, 40);
							int32 RandY = FMath::RandRange(-60, 0);
							MakePanel->SetPosition(FVector2D(RandX,RandY));
							
							
						}
					}
				}
			}
		}
	}
}

void UBaseProgressBarWidget::OnWeakEvent()
{
	if (Weak)
	{
		Weak->PlayFloatingAnimation();
		bIsWeak= true;
	}
}

void UBaseProgressBarWidget::OnCriticalEvent()
{
	if(Critical)
	{
		Critical->PlayFloatingAnimation();
	}
}

void UBaseProgressBarWidget::OnResistEvent()
{
	if (Resist)
	{
		Resist->PlayFloatingAnimation();
	}
}

void UBaseProgressBarWidget::OnMissEvent()
{
	if (MissAnim && Miss)
	{
		PlayAnimation(MissAnim);
		Miss->PlayFloatingAnimation();
	}
}

void UBaseProgressBarWidget::OnTurnEndEvent()
{
	PlayProgressAnimation(EProgressBarAnimType::Reset);
	UpdateHPBarRate();

	if (RootDamageGroup)
	{
		RootDamageGroup->ClearChildren();
	}
}

void UBaseProgressBarWidget::UpdateHPBar()
{
	if (WidgetOwner)
	{
		const FStatus& MakeStatus = WidgetOwner->StatusComponent->Get_Status();

		HPBar->SetPercent(NormalizeProgressBarPercent(MakeStatus.MaxHp,MakeStatus.CurrentHp));
	}
}

void UBaseProgressBarWidget::UpdateHPBarRate()
{
	HPBarRate->SetPercent(HPBar->GetPercent());
}
