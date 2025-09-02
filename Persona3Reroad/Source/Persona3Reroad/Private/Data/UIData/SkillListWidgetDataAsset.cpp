// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/SkillListWidgetDataAsset.h"

USkillListWidgetDataAsset::USkillListWidgetDataAsset()
{
}

UPaperSprite* USkillListWidgetDataAsset::GetSkillCostSprite(const int32 Index)
{
	if (SkillCostSpriteArray.IsValidIndex(Index))
	{
		if (UPaperSprite* MakeSprite = SkillCostSpriteArray[Index])
		{
			return MakeSprite;
		}
	}
	return nullptr;
}

UPaperSprite* USkillListWidgetDataAsset::FindCostTypeSprite(const FName Name)
{
	if (TObjectPtr<UPaperSprite>* MakeSprite = CostTypeSpriteMap.Find(Name))
	{
		return MakeSprite->Get();
	}
	return nullptr;
}

FLinearColor* USkillListWidgetDataAsset::FindCostColor(const FName Name)
{
	if (FLinearColor* MakeColor = CostColorMap.Find(Name))
	{
		return MakeColor;
	}
	return nullptr;
}

UPaperSprite* USkillListWidgetDataAsset::FindSkillTypeSprite(const EElement& InElement)
{
	if (TObjectPtr<UPaperSprite>* MakeSprite = SkillTypeSpriteMap.Find(InElement))
	{
		return MakeSprite->Get();
	}
	return nullptr;
}
