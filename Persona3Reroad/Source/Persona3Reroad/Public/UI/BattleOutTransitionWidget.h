// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BattleOutTransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBattleOutTransitionWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	

	UBattleOutTransitionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:

	UFUNCTION(BlueprintCallable)
	void FadeOutEvent();

	UPROPERTY(Transient,BlueprintReadWrite,meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	
	
};
