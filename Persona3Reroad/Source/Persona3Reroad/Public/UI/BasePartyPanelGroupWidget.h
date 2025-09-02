// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BasePartyPanelGroupWidget.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBasePartyPanelGroupWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBasePartyPanelGroupWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void AddViewportEvent(const int32& InZOrder) override;
	virtual void RemoveViewportEvent() override;

	virtual UBaseUIWidget* FindPanelWidget(const FName& InName);
	virtual void PlayGroupAnimation();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Party Panel Battle Group",meta=(BindWidget,AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> Group;
	
	
	
};
