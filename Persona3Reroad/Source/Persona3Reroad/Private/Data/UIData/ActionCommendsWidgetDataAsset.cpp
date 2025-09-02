// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/ActionCommendsWidgetDataAsset.h"

FLinearColor* UActionCommendsWidgetDataAsset::FindColor(const FName Name)
{
	if (FLinearColor* Color = ColorGroup.Find(Name))
	{
		return Color;
	}
	return nullptr;
}
