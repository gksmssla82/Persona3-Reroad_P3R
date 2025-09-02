// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "PartyPanelFieldDataAsset.generated.h"

class UPaperSprite;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelFieldDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()

public:
	UPaperSprite* FindFaceMap(const FName& InName);

private:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TMap<FName,TObjectPtr<UPaperSprite>> FaceMap;
	
};
