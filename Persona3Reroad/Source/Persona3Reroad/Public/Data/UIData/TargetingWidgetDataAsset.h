// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "TargetingWidgetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTargetingWidgetDataAsset : public UBaseInputWidgetDataAsset
{
	GENERATED_BODY()
public:
	UInputMappingContext* GetInputMappingContextCancel() const;
	UInputAction* FindInputActionCancel(const FName Name);
	
private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CancleInput" , meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> InputMappingContextCancel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CancleInput" , meta = (AllowPrivateAccess = true))
	TMap<FName,TObjectPtr<UInputAction>> InputActionGroupCancel;
};
