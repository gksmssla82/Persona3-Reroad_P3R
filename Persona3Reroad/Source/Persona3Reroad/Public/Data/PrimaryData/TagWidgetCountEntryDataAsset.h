// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "TagWidgetCountEntryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTagWidgetCountEntryDataAsset : public UBaseWidgetPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE TArray<FTagWidgetCountEntry> GetTagWidgetCountEntry() const {return TagWidgetCountEntry;};
	
private:
	UPROPERTY(EditAnywhere, Category = "FTagWidgetCountEntry")
	TArray<FTagWidgetCountEntry> TagWidgetCountEntry;
};
