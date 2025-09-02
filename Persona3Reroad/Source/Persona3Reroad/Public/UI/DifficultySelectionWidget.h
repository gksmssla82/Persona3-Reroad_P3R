// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "DifficultySelectionWidget.generated.h"

DECLARE_DELEGATE(OnButtonDelegate);

class UDifficultyWidgetDataAsset;

UCLASS()
class PERSONA3REROAD_API UDifficultySelectionWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	UDifficultySelectionWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	//Input Action
	void Input_UpStarted();
	void Input_DownStarted();
	void Input_ConfirmStarted();
	void Input_CancelStarted();

	//PlayAnim
	void PlayInputAnimation_Forward();
	void PlayInputAnimation_Reverse();
	
	UFUNCTION(BlueprintCallable)
	void PlayButtonAnimation();

	//Button Event
	void OnPeacefulEvent();
	void OnEasyEvent();
	void OnNormalEvent();
	void OnHardEvent();
	void OnLunaticEvent();

	//Set Array
	void SetThisClassArray();

	UFUNCTION(BlueprintCallable)
	void OpenNormalLevel();

	//Data Asset
	UPROPERTY()
	TObjectPtr<UDifficultyWidgetDataAsset> WidgetDataAsset;

	//OnButton Function Array
	TArray<OnButtonDelegate> OnButtonFunctionArray;

	//Current Index
	UPROPERTY()
	int32 CurrentButtonIndex;

	UPROPERTY(BlueprintReadWrite,meta = (AllowPrivateAccess = true))
	bool bIsPressedUpDownKey;


	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> RemoveAnim;


	//Button Animation
	UPROPERTY()
	TArray<UWidgetAnimation*> ButtonAnimationArray;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> PeacefulAnim;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> EasyAnim;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> NormalAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> HardAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> LunaticAnim;




	//BlueBar Animation
	UPROPERTY()
	TArray<UWidgetAnimation*> BlueBarAnimationArray;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar0To1;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar1To2;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar2To3;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar3To4;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar4To0;

	//Reset Animation
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> ResetButtonAnim;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Difficulty Selection",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> NormalButtonEventAnim;
};
