// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/BaseProgressBarDataAsset.h"

#include "UI/CombatDamageGroupWidget.h"

UBaseProgressBarDataAsset::UBaseProgressBarDataAsset()
{
}

TSubclassOf<UCombatDamageGroupWidget> UBaseProgressBarDataAsset::GetCombatDamageGroup() const
{
	if (CombatDamageGroup)
	{
		return CombatDamageGroup;
	}
	return nullptr;
}
