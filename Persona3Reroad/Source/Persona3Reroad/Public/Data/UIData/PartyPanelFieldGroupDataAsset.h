// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "PartyPanelFieldGroupDataAsset.generated.h"

class UBaseUIWidget;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelFieldGroupDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE TSubclassOf<UBaseUIWidget> GetPartyPanelFieldWidget() const {return PartyPanelFieldWidget;}
private:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Party Panel Battle",meta = (AllowPrivateAccess = true))
	TSubclassOf<UBaseUIWidget> PartyPanelFieldWidget;
	
};
