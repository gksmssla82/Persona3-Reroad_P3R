// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionCommendsWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagsManager.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Components/StatusComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/UIData/ActionCommendsWidgetDataAsset.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "Elements/Framework/TypedElementQueryBuilder.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/PersonaGameInstance.h"
#include "System/WidgetInstanceSubsystem.h"
#include "UI/TargetingWidget.h"

UActionCommendsWidget::UActionCommendsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UActionCommendsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UActionCommendsWidgetDataAsset>(BaseDataAsset);
	}

	BIPair.Add(EActionCommends::Attack, FButtonImagePair(Attack, AttackButton));
	BIPair.Add(EActionCommends::Skill, FButtonImagePair(Skill, SkillButton));
	BIPair.Add(EActionCommends::Guard, FButtonImagePair(Guard, GuardButton));
	BIPair.Add(EActionCommends::Item, FButtonImagePair(Item, ItemButton));

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				// //Attack //타겟 컴뱃에서 처리
				// if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Attack"))
				// {
				// 	EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				// 	                                   &UActionCommendsWidget::OnAttackButtonClicked);
				// }
				//Skill
				if (UInputAction* InputActionSkill = WidgetDataAsset->FindInputAction("Skill"))
				{
					EnhancedInputComponent->BindAction(InputActionSkill, ETriggerEvent::Started, this,
					                                   &UActionCommendsWidget::OnSkillButtonClicked);
				}
				//Guard
				if (UInputAction* InputActionGuard = WidgetDataAsset->FindInputAction("Guard"))
				{
					EnhancedInputComponent->BindAction(InputActionGuard, ETriggerEvent::Started, this,
					                                   &UActionCommendsWidget::OnGuardButtonClicked);
				}
				//Item
				if (UInputAction* InputActionItem = WidgetDataAsset->FindInputAction("Item"))
				{
					EnhancedInputComponent->BindAction(InputActionItem, ETriggerEvent::Started, this,
					                                   &UActionCommendsWidget::OnItemButtonClicked);
				}
				//Shift
				if (UInputAction* InputActionShift = WidgetDataAsset->FindInputAction("Shift"))
				{
					EnhancedInputComponent->BindAction(InputActionShift, ETriggerEvent::Started, this,
					                                   &UActionCommendsWidget::OnShiftButtonClicked);
				}
			}
		}
	}
}

void UActionCommendsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

void UActionCommendsWidget::AddViewportEvent()
{
	this->AddToViewport();

	if(AActor* MakeActor = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetTargetController())
	{
		if (ATargetingCombatWidgetActor* MakeTargetCombat = Cast<ATargetingCombatWidgetActor>(MakeActor))
		{
			if (UTargetingWidget* MakeWidget = Cast<UTargetingWidget>(MakeTargetCombat->GetWidgetComponent()->GetWidget()))
			{
				if (UBattleInstanceSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
				{
					ATBC_CharacterBase* Character = Subsystem->TurnOrder[0];
					Character->CurrentSkill = nullptr;
					Character->StatusComponent->Set_ElementAttck(Character->SkillList[0]->GetSkillInfo().SkillElement);
				}
				
				MakeWidget->StartActionTargeting();
			}
		}
	}

	// Stance Tag Add
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->
	Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("Stance.SelectSkill"));
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->
	Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("Stance.SelectCommend"));
}

void UActionCommendsWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();

	//EndActionTargeting
	if(AActor* MakeActor = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetTargetController())
	{
		if (ATargetingCombatWidgetActor* MakeTargetCombat = Cast<ATargetingCombatWidgetActor>(MakeActor))
		{
			if (UTargetingWidget* MakeWidget = Cast<UTargetingWidget>(MakeTargetCombat->GetWidgetComponent()->GetWidget()))
			{
				
				MakeWidget->EndActionTargeting();
			}
		}
	}

	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->
	Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("Stance.SelectCommend"));
}

void UActionCommendsWidget::OnAttackButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("GO Attack"));
}

void UActionCommendsWidget::OnSkillButtonClicked()
{
	FName TagName = FName("Widget.Battle.SkillCommends");

	if (UPersonaGameInstance* MakeGameInstance = Cast<UPersonaGameInstance>(GetGameInstance()))
	{
		if (UWidgetInstanceSubsystem* MakeSubsystem = MakeGameInstance->GetSubsystem<UWidgetInstanceSubsystem>())
		{
			if (UGameplayTagsManager::Get().RequestGameplayTag(TagName, false).IsValid())
			{
				//push SkillCommend
				FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(TagName, false);
				if (UBaseUIWidget* MakeWidget = MakeSubsystem->FindRegistryWidgetMap(Tag))
				{
					UGameplayStatics::PlaySound2D(GetWorld(), SelectCommendSfx);
					MakeSubsystem->PushWidget(MakeWidget);
				}
			}
		}
	}
}

void UActionCommendsWidget::OnGuardButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("GO Guard"))

	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->
	Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("Stance.Guard"));
}

void UActionCommendsWidget::OnItemButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Item Widget"));
}

void UActionCommendsWidget::OnShiftButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnShiftButtonClicked"));
}
