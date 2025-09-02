// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "BaseProgressBarDataAsset.generated.h"

class UCombatDamageGroupWidget;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseProgressBarDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	UBaseProgressBarDataAsset();
	
	TSubclassOf<UCombatDamageGroupWidget> GetCombatDamageGroup() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress", meta = (AllowPrivateAccess = true))
	TSubclassOf<UCombatDamageGroupWidget> CombatDamageGroup;
};
