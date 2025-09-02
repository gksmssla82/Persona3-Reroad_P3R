// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/PartyPanelBattleDataAsset.h"

UPartyPanelBattleDataAsset::UPartyPanelBattleDataAsset()
	: Super()
{
}

FPartyPanelBattleFaceGroup* UPartyPanelBattleDataAsset::FindPartyFaceGroup(const FName Name)
{
	if (FPartyPanelBattleFaceGroup* FaceGroup = PartyFaceGroup.Find(Name))
	{
		return FaceGroup;
	}
	return nullptr;
}

FSprite2D* UPartyPanelBattleDataAsset::FindStateText(const int32 Num)
{
	if (FSprite2D* TextSprite2D = StateText.Find(Num))
	{
		return TextSprite2D;
	}
	return nullptr;
}

FLinearColor* UPartyPanelBattleDataAsset::FindColor(const FName Name)
{
	if (FLinearColor* LinearColor = Color.Find(Name))
	{
		return LinearColor;
	}
	return nullptr;
}


