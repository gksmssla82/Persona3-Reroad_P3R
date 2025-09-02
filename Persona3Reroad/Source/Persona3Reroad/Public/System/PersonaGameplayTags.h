// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace PersonaGamePlayTags
{
	// Input Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CamMove);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Attack);

	// Stance Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stance_SelectCommend);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stance_SelectSkill);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stance_Guard);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stance_Summon);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_IsDead);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Resist);

	// State Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Sturn);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Evasion);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_TakeCritical);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_OneMore);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Weak);
	
}



//Widget GamePlayTags
namespace WidgetGamePlayTags
{
	//Global Widget
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Global_Day);

	//Title Widget
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Title_PressAnyButton);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Title_VerticalMenu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Title_DifficultySelection);
	
	//Battle Widget
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_ActionCommends);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_SkillCommends);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_PartyPanel_Field);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_PartyPanel_Battle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_PartyPanel_Pause);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_NamePlate_Monster);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_NamePlate_MonsterSkill);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_NamePlate_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_NamePlate_PlayerSkill);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_AllOutAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Battle_BattleOutButton);
	

	//Transition Widget
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Transition_InTurnBattle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Transition_AllOutFinish);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Transition_BattleResult);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Transition_BattleOutTransition);

	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Transition_ToLoadLevel);
	
	//Combat Widget
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Combat_Damage);
	
	//TargetController
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_Combat_TargetController);

	//MiniMap
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Widget_MiniMap_BattleMiniMap);
}
