// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "TitleToLoadLevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTitleToLoadLevelWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	UTitleToLoadLevelWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	UFUNCTION()
	void OnLevelLoaded();

	UFUNCTION(BlueprintCallable)
	void FadeInEvent();

private:
	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite,meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> RemoveAnim;
	
};
