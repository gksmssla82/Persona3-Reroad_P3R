// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/InputDataAsset.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "BaseInputWidgetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseInputWidgetDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	UInputMappingContext* GetInputMappingContext() const;
	UInputAction* FindInputAction(const FName Name);
	
private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input" , meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input" , meta = (AllowPrivateAccess = true))
	TMap<FName,TObjectPtr<UInputAction>> InputActionGroup;
	
};
