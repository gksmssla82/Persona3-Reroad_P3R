// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BasePartyPanelGroupWidget.h"
#include "PartyPanelFieldGroupWidget.generated.h"

class UPartyPanelFieldGroupDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelFieldGroupWidget : public UBasePartyPanelGroupWidget
{
	GENERATED_BODY()
public:
	UPartyPanelFieldGroupWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	UFUNCTION(BlueprintCallable, Category = "PartyPanelBattleGroupWidget")
	void Init_PartyPanelGroup();
	
	UPROPERTY()
	TObjectPtr<UPartyPanelFieldGroupDataAsset> WidgetDataAsset;

	UPROPERTY()
	bool bIsPartyPanelSetting;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> RemoveAnim;
};
