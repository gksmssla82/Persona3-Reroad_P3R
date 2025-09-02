// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseFloatingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseFloatingWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBaseFloatingWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	void PlayFloatingAnimation();

private:

	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> Reset;

	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> CreateAnim;
	
};
