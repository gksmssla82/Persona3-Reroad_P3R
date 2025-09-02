// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseInputWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseInputWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBaseInputWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void AddWidgetMappingContext();
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void RemoveWidgetMappingContext();
	
	virtual void OnVisibility();

	void SetInputModeUIOnly(const bool& bMouseActivate = false);
	void SetInputModeGameAndUI(const bool& bMouseActivate = false);
	void SetInputModeGameOnly(const bool& bMouseActivate = false);

	
	
};
