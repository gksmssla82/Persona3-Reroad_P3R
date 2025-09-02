// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/TargetingWidgetDataAsset.h"

UInputMappingContext* UTargetingWidgetDataAsset::GetInputMappingContextCancel() const
{
	if (InputMappingContextCancel)
	{
		return InputMappingContextCancel;
	}
	return nullptr;
}

UInputAction* UTargetingWidgetDataAsset::FindInputActionCancel(const FName Name)
{
	if (TObjectPtr<UInputAction>* MakeInputAction = InputActionGroupCancel.Find(Name))
	{
		return *MakeInputAction;
	}
	return nullptr;
}
