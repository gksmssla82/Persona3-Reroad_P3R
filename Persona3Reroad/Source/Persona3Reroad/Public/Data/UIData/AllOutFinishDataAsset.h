// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "AllOutFinishDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAllOutFinishDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	UMaterialInstance* FindFinishMaterials(const FName& InName);
	
private:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta = (AllowPrivateAccess = true))
	TMap<FName,TObjectPtr<UMaterialInstance>> FinishMaterialsMap;
	
};
