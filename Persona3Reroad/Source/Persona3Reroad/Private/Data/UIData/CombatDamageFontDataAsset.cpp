// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/CombatDamageFontDataAsset.h"

FSprite2D* UCombatDamageFontDataAsset::GetDamageFontSprite2D(const int32& InNumber)
{
	if (DamageFontSprite2D.IsValidIndex(InNumber))
	{
		return &DamageFontSprite2D[InNumber];
	}
	return nullptr;
}

FLinearColor* UCombatDamageFontDataAsset::FindDamageFontColor(const FName& InName)
{
	if (FLinearColor* MakeColor = DamageFontColor.Find(InName))
	{
		return MakeColor;
	}
	return nullptr;
}
