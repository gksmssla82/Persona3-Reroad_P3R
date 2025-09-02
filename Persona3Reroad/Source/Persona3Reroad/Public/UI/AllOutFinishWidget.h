// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "AllOutFinishWidget.generated.h"

class UAllOutFinishDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAllOutFinishWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UAllOutFinishWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	//Data Asset
	UPROPERTY()
	TObjectPtr<UAllOutFinishDataAsset> WidgetDataAsset;

	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Finish",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	//Widget Image
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="All Out Finish",meta = (BindWidget,AllowPrivateAccess = true))
	TObjectPtr<UImage> FinishMaterial;
	
};
