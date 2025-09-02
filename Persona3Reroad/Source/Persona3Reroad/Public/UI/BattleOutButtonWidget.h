// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "BattleOutButtonWidget.generated.h"

class UBattleOutButtonDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBattleOutButtonWidget : public UBaseInputWidget
{
	GENERATED_BODY()
public:
	
	UBattleOutButtonWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	void Input_ConfirmStarted();

	UFUNCTION(BlueprintCallable)
	void OnConfirmButtonEvent();

	UPROPERTY()
	TObjectPtr<UBattleOutButtonDataAsset> WidgetDataAsset;

	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Attack",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Attack",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> ConfirmButtenAnim;
	
};
