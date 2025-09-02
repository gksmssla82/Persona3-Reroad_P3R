// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "AllOutAttackInputWidget.generated.h"


class UAllOutAttackWidgetDataAsset;

UCLASS()
class PERSONA3REROAD_API UAllOutAttackInputWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	UAllOutAttackInputWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

protected:

	void Input_ConfirmStarted();
	void Input_CancelStarted();


	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnConfirmButtenEvent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnCanCelButtenEvent();

private:

	UPROPERTY()
	TObjectPtr<UAllOutAttackWidgetDataAsset> WidgetDataAsset;

	//Widget Animation
	
	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Attack",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Attack",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> ConfirmButtenAnim;

	UPROPERTY(Transient,BlueprintReadWrite,Category="All Out Attack",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CancelButtenAnim;
	
	
	
	
};
