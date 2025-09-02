// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/TBCP_AnimInstanceBase.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"

UTBCP_AnimInstanceBase::UTBCP_AnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UTBCP_AnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (IsValid(Character))
	{
		TurnBasedCharacter = Cast<ATBC_PlayerBase>(Character);
		StatusComponent = Cast<UStatusComponent>(TurnBasedCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	}
}

void UTBCP_AnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(TurnBasedCharacter))
	{
		bIsBattleStart = TurnBasedCharacter->bIsBattleStart;
	}

	if (IsValid(StatusComponent))
	{
		bIsSelectCommend = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.SelectCommend"));
		bIsSelectSKill = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.SelectSkill"));
		bIsGuard = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Guard"));
		bIsSummon = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Summon"));
		bIsSturn = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn"));
	}
	
}
