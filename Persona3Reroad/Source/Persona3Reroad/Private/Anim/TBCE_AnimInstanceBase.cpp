// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/TBCE_AnimInstanceBase.h"

#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"

UTBCE_AnimInstanceBase::UTBCE_AnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UTBCE_AnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (IsValid(Character))
	{
		TurnBasedCharacter = Cast<ATBC_EnemyBase>(Character);
		StatusComponent = Cast<UStatusComponent>(TurnBasedCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	}
}

void UTBCE_AnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(StatusComponent))
	{
		bIsSturn = StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn"));
		bIsDead =  StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead"));
	}
}
