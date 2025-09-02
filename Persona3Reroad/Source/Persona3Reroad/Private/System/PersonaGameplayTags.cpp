// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PersonaGameplayTags.h"

namespace PersonaGamePlayTags
{
	//Input
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_CamMove, "Input.Action.CamMove");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Sprint, "Input.Action.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Attack, "Input.Action.Attack");

	//Stance
	UE_DEFINE_GAMEPLAY_TAG(Stance_SelectCommend, "Stance.SelectCommend");
	UE_DEFINE_GAMEPLAY_TAG(Stance_SelectSkill, "Stance.SelectSkill");
	UE_DEFINE_GAMEPLAY_TAG(Stance_Guard, "Stance.Guard");
	UE_DEFINE_GAMEPLAY_TAG(Stance_Summon, "Stance.Summon");

	//State
	UE_DEFINE_GAMEPLAY_TAG(State_Sturn, "State.Sturn");
	UE_DEFINE_GAMEPLAY_TAG(State_Evasion, "State.Evasion");
	UE_DEFINE_GAMEPLAY_TAG(State_TakeCritical, "State.TakeCritical");
	UE_DEFINE_GAMEPLAY_TAG(State_IsDead, "State.IsDead");
	UE_DEFINE_GAMEPLAY_TAG(State_OneMore, "State.OneMore");
	UE_DEFINE_GAMEPLAY_TAG(State_Weak, "State.Weak");
	UE_DEFINE_GAMEPLAY_TAG(State_Resist, "State.Resist");
}

namespace WidgetGamePlayTags
{
	//Global Widget
	UE_DEFINE_GAMEPLAY_TAG(Widget_Global_Day, "Widget.Global.Day");

	//Title Widget
	UE_DEFINE_GAMEPLAY_TAG(Widget_Title_PressAnyButton, "Widget.Title.PressAnyButton");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Title_VerticalMenu, "Widget.Title.VerticalMenu");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Title_DifficultySelection, "Widget.Title.DifficultySelection");

	//Battle Widget
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_ActionCommends, "Widget.Battle.ActionCommends");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_SkillCommends, "Widget.Battle.SkillCommends");

	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_PartyPanel_Field, "Widget.Battle.PartyPanel.Field");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_PartyPanel_Battle, "Widget.Battle.PartyPanel.Battle");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_PartyPanel_Pause, "Widget.Battle.PartyPanel.Pause");

	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_NamePlate_Monster, "Widget.Battle.NamePlate.Monster");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_NamePlate_MonsterSkill, "Widget.Battle.NamePlate.MonsterSkill");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_NamePlate_Player, "Widget.Battle.NamePlate.Player");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_NamePlate_PlayerSkill, "Widget.Battle.NamePlate.PlayerSkill");

	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_AllOutAttack, "Widget.Battle.AllOutAttack");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Battle_BattleOutButton, "Widget.Battle.BattleOutButton");
	

	//Transition Widget
	UE_DEFINE_GAMEPLAY_TAG(Widget_Transition_InTurnBattle, "Widget.Transition.InTurnBattle");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Transition_AllOutFinish, "Widget.Transition.AllOutFinish");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Transition_BattleResult, "Widget.Transition.BattleResult");
	UE_DEFINE_GAMEPLAY_TAG(Widget_Transition_BattleOutTransition, "Widget.Transition.BattleOutTransition");
	

	UE_DEFINE_GAMEPLAY_TAG(Widget_Transition_ToLoadLevel, "Widget.Transition.ToLoadLevel");
	
	
	//Combat Widget
	UE_DEFINE_GAMEPLAY_TAG(Widget_Combat_Damage, "Widget.Combat.Damage");

	//TargetController
	UE_DEFINE_GAMEPLAY_TAG(Widget_Combat_TargetController, "Widget.Combat.TargetController");

	//MiniMap
	UE_DEFINE_GAMEPLAY_TAG(Widget_MiniMap_BattleMiniMap, "Widget.MiniMap.BattleMiniMap");
	
}