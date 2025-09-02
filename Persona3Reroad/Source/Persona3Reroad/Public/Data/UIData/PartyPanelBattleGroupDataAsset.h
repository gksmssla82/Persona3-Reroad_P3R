// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "PartyPanelBattleGroupDataAsset.generated.h"

class UBaseUIWidget;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelBattleGroupDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
public:
	UPartyPanelBattleGroupDataAsset();

	FORCEINLINE TSubclassOf<UBaseUIWidget> GetPartyPanelBattleWidget() const {return PartyPanelBattleWidget;}

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Party Panel Battle",meta = (AllowPrivateAccess = true))
	TSubclassOf<UBaseUIWidget> PartyPanelBattleWidget;
	
	
};
