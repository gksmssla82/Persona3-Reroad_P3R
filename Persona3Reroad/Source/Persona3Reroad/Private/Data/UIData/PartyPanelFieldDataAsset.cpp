// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/PartyPanelFieldDataAsset.h"

UPaperSprite* UPartyPanelFieldDataAsset::FindFaceMap(const FName& InName)
{
	if (FaceMap.Contains(InName))
	{
		return *FaceMap.Find(InName);
	}
	return nullptr;
}
