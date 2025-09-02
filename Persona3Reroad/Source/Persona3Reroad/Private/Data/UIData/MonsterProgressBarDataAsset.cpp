// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/MonsterProgressBarDataAsset.h"

UPaperSprite* UMonsterProgressBarDataAsset::FindElementImage(const EElement& InElement)
{
	if (ElementImage.Contains(InElement))
	{
		if (UPaperSprite* FaceGroup = *ElementImage.Find(InElement))
		{
			return FaceGroup;
		}
	}
	return nullptr;
}
