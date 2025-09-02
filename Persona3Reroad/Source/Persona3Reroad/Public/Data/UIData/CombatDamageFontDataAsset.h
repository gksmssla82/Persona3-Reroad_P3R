// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "Structs/WidgetStructs.h"
#include "CombatDamageFontDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UCombatDamageFontDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	FSprite2D* GetDamageFontSprite2D(const int32& InNumber);
	FLinearColor* FindDamageFontColor(const FName& InName);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage Font",meta = (AllowPrivateAccess = true))
	TArray<FSprite2D> DamageFontSprite2D;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage Font Color",meta = (AllowPrivateAccess = true))
	TMap<FName, FLinearColor> DamageFontColor;
	
};
