// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "CombatDamageGroupWidget.generated.h"

class UHorizontalBox;
class UCombatDamageGroupDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UCombatDamageGroupWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	UCombatDamageGroupWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Init_CombatDamageGroup(const int32& InDamage,const bool& bIsWeak = false);

	void PlayDamageGroupAnimation();

private:

	//Data Asset
	UPROPERTY()
	TObjectPtr<UCombatDamageGroupDataAsset> WidgetDataAsset;
	
	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Damage",
		meta = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Reset;

	//Horizontal Box
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UHorizontalBox> HorizontalDamageBox;
	
};
