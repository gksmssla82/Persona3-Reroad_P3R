// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseNamePlateWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseNamePlateWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	UBaseNamePlateWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	virtual void SetNamePlate(const FText& NewNamePlate);

	
private:

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Widget Plate",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	//TextBlock
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Plate",meta = (BindWidget,AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> PlateTextBlock;
	
};
