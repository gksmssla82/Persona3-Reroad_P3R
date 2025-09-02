// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/SkillCommendsWidgetDataAsset.h"

#include "UI/SkillListWidget.h"

FLinearColor* USkillCommendsWidgetDataAsset::GetSkillDescriptionColor()
{
	return &SkillDescriptionColor;
}

UFont* USkillCommendsWidgetDataAsset::GetSkillDescriptionFont()
{
	if (SkillDescriptionFont)
	{
		return SkillDescriptionFont;
	}
	return nullptr;
}

TSubclassOf<USkillListWidget> USkillCommendsWidgetDataAsset::GetSkillListWidgetClass()
{
	if (SkillListWidgetClass)
	{
		return SkillListWidgetClass;
	}
	return nullptr;
}

UTexture2D* USkillCommendsWidgetDataAsset::FindPersonaTexture(const FName& InPersonaName)
{
	if (PersonaTextureTMap.Contains(InPersonaName))
	{
		return *PersonaTextureTMap.Find(InPersonaName);
	}
	return nullptr;
}
