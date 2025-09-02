// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputDataAsset.h"

const UInputAction* UInputDataAsset::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FPersonaInputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
			
	}

	UE_LOG(LogTemp, Error, TEXT("Can't Find InputAction For Tag = [%s]"), *InputTag.ToString());

	return nullptr;
}
