// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseTransitionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseTransitionWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	
	UBaseTransitionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
private:
	UPROPERTY(Transient,BlueprintReadWrite,meta=(BindWidgetAnim,AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> TransitionAnim;
	
	
};
