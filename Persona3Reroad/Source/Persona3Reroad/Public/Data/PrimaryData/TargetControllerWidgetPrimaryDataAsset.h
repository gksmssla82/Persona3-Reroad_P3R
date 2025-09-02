// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "TargetControllerWidgetPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTargetControllerWidgetPrimaryDataAsset : public UBaseWidgetPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE FTagCombatPair GetTagCombatPair() const {return TagCombatPair;}
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnArray" ,meta = (AllowPrivateAccess = true))
	FTagCombatPair TagCombatPair;
	
};
