// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/AllOutFinishDataAsset.h"

UMaterialInstance* UAllOutFinishDataAsset::FindFinishMaterials(const FName& InName)
{
	if (FinishMaterialsMap.Contains(InName))
	{
		return *FinishMaterialsMap.Find(InName);
	}
	return nullptr;
}
