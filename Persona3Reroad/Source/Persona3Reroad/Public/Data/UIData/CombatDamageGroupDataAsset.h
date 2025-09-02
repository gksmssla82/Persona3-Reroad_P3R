// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "UI/CombatDamageFontUIWidget.h"
#include "CombatDamageGroupDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UCombatDamageGroupDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE TSubclassOf<UCombatDamageFontUIWidget> GetDamageFontClass() {return DamageFontClass;}

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Damage Font Class", meta = (AllowPrivateAccess = true))
	TSubclassOf<UCombatDamageFontUIWidget> DamageFontClass;
	
};
  