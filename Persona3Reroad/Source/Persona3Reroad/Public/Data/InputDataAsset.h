// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT()
struct FPersonaInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
};

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TArray<FPersonaInputAction> InputActions;
	
};
