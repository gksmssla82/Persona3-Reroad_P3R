// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "DayWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UDayWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	UDayWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> RemoveAnim;
	
};
