// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UIData/BaseInputWidgetDataAsset.h"

UInputMappingContext* UBaseInputWidgetDataAsset::GetInputMappingContext() const
{
	if (InputMappingContext)
	{
		return InputMappingContext;
	}
	return nullptr;
}

UInputAction* UBaseInputWidgetDataAsset::FindInputAction(const FName Name)
{
	if (TObjectPtr<UInputAction>* MakeInputAction = InputActionGroup.Find(Name))
	{
		return *MakeInputAction;
	}
	return nullptr;
}
