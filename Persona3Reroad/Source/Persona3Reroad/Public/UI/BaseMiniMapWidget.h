// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseMiniMapWidget.generated.h"

class ATPS_Enemy_Trigger01;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseMiniMapWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBaseMiniMapWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	UPROPERTY(Transient,BlueprintReadWrite,Category="MiniMap",meta=(BindWidgetAnim,AllowPrivateAccess="true"))
	TObjectPtr<UWidgetAnimation> ScreenIn;

	UPROPERTY(Transient,BlueprintReadWrite,Category="MiniMap",meta=(BindWidgetAnim,AllowPrivateAccess="true"))
	TObjectPtr<UWidgetAnimation> ScreenOut;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy", meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<ATPS_Enemy_Trigger01>> TriggerEnemys;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy", meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<UUserWidget>> WidgetEnemys;
};
