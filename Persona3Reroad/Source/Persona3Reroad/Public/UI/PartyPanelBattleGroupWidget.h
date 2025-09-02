// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BasePartyPanelGroupWidget.h"
#include "PartyPanelBattleGroupWidget.generated.h"

class UPartyPanelFieldGroupDataAsset;
class UPartyPanelBattleGroupDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelBattleGroupWidget : public UBasePartyPanelGroupWidget
{
	GENERATED_BODY()

public:
	UPartyPanelBattleGroupWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void AddViewportEvent(const int32& InZOrder) override;
	virtual void RemoveViewportEvent() override;

	virtual void PlayGroupAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "PartyPanelBattleGroupWidget")
	void Init_PartyPanelGroup();

private:
	UPROPERTY()
	TObjectPtr<UPartyPanelBattleGroupDataAsset> WidgetDataAsset;

	UPROPERTY()
	bool bIsPartyPanelSetting;
	
};
