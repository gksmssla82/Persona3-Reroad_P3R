// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "PressAnyButtonWidget.generated.h"

class UPressAnyButtonWidgetDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPressAnyButtonWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	UPressAnyButtonWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;
private:

	void Input_ConfirmStarted();
	UPROPERTY()
	TObjectPtr<UPressAnyButtonWidgetDataAsset> WidgetDataAsset;
	
	
	UPROPERTY(Transient,BlueprintReadWrite,Category="Press Any Button",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Reset;
	
	UPROPERTY(Transient,BlueprintReadWrite,Category="Press Any Button",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;
	
	UPROPERTY(Transient,BlueprintReadWrite,Category="Press Any Button",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> TextAnim;
	
	UPROPERTY(Transient,BlueprintReadWrite,Category="Press Any Button",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> RemoveAnim;
	
	
};
