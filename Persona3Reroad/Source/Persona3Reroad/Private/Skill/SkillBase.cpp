// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBase.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"

USkillBase::USkillBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void USkillBase::Set_Element(const ATBC_CharacterBase* Character) 
{
	Character->StatusComponent->Set_ElementAttck(SkillInfo.SkillElement);
}
