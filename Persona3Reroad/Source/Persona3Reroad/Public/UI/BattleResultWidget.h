// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BattleResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBattleResultWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBattleResultWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Finish",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;
	
};
