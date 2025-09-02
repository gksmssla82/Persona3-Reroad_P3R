// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "ActionCommendsWidgetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UActionCommendsWidgetDataAsset : public UBaseInputWidgetDataAsset
{
	GENERATED_BODY()
public:
	FLinearColor* FindColor(const FName Name);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color" ,meta = (AllowPrivateAccess = true))
	TMap<FName, FLinearColor> ColorGroup;
	
};
