// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseCombatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseCombatWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBaseCombatWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void PlayCombatAnimation();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",meta=(BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;
	

	
	
};
