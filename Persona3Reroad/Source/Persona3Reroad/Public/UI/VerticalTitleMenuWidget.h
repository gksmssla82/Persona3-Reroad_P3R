// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "VerticalTitleMenuWidget.generated.h"

class ULevelSequencePlayer;
class ULevelSequence;
DECLARE_DELEGATE(OnButtonDelegate);

class UVerticalMainManuWidgetDataAsset;

UCLASS()
class PERSONA3REROAD_API UVerticalTitleMenuWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	UVerticalTitleMenuWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:

	//Input Action
	void Input_UpStarted();
	void Input_DownStarted();
	void Input_ConfirmStarted();
	void Input_ExitGameStarted();

	//Button Event
	void OnNewGameEvent();
	void OnLoadGameEvent();
	void OnConfigEvent();

	//Set AnimArray
	void SetThisClassArray();

	//PlayAnim
	void PlayInputAnimation_Forward();
	void PlayInputAnimation_Reverse();
	void PlayButtonAnimation();
	
	//Data Asset
	UPROPERTY()
	TObjectPtr<UVerticalMainManuWidgetDataAsset> WidgetDataAsset;

	//Current Index
	UPROPERTY()
	int32 CurrentButtonIndex;

	//Construct Check
	UPROPERTY()
	bool bIsPlayedCreateAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bIsPressedUpDownKey;

	//OnButton Function Array
	TArray<OnButtonDelegate> OnButtonFunctionArray;
	
	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	//Button Animation
	UPROPERTY()
	TArray<UWidgetAnimation*> ButtonAnimationArray;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> NewGameAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> LoadGameAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> ConfigAnim;


	//BlueBar Animation
	UPROPERTY()
	TArray<UWidgetAnimation*> BlueBarAnimationArray;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar_0To1;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar_1To2;

	UPROPERTY(Transient, BlueprintReadWrite, Category="Vertical Main Menu",
		meta=(BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> BlueBar_2To0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<ULevelSequencePlayer> LevelSequence;


	
};
