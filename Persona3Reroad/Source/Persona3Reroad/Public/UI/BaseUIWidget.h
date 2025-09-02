// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "Structs/WidgetStructs.h"
#include "BaseUIWidget.generated.h"


class UPaperSprite;
class UImage;


//Persona widget 최상위 부모 클래스

UCLASS(BlueprintType)
class PERSONA3REROAD_API UBaseUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBaseUIWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	virtual void AddViewportEvent();

	//UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	virtual void AddViewportEvent(const int32& InZOrder);

	UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	virtual void RemoveViewportEvent();

	UFUNCTION(BlueprintCallable, Category = "BaseWidget")
	virtual void PlayAnim_Hidden();
	
protected:
	//굳이 안쓸거같지만 아직안지우는애들
	void SetBrushFromSprite(UImage* Image, UPaperSprite* Sprite);
	void SetBrushFromSprite2D(const FUImage2D* Image2D, const FSprite2D* Sprite2D);

	//사용중
	float NormalizeProgressBarPercent(const float Max, const float Current) const;
	TArray<int32> SplitNumberIntoDigits(const int32& State);

	



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BaseUIDataAsset", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBaseUIDataAsset> BaseDataAsset;
};
