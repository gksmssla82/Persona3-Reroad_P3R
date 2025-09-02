// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "TagWidgetPairPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTagWidgetPairPrimaryDataAsset : public UBaseWidgetPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE TArray<FTagWidgetPair> GetTagWidgetPairArray() const {return TagWidgetPairArray;};
	
private:
	UPROPERTY(EditAnywhere, Category = "FTagWidgetPairArray")
	TArray<FTagWidgetPair> TagWidgetPairArray;
};
