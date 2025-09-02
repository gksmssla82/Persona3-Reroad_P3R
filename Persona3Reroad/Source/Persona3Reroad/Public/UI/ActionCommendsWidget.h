// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UI/BaseInputWidget.h"
#include "ActionCommendsWidget.generated.h"

UENUM(BlueprintType)
enum class EActionCommends : uint8
{
	Attack,
	Skill,
	Guard,
	Item,
	Shift
};

USTRUCT()
struct FButtonImagePair
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "BI Pair")
	TObjectPtr<UImage> Image;

	UPROPERTY(EditAnywhere, Category = "BI Pair")
	TObjectPtr<UButton> Button;

	FButtonImagePair()
		: Image(nullptr)
		  , Button(nullptr)
	{
	}

	FButtonImagePair(const TObjectPtr<UImage>& InImage, const TObjectPtr<UButton>& InButton)
		: Image(InImage)
		  , Button(InButton)
	{
	}
};

class UImage;
class UActionCommendsWidgetDataAsset;

UCLASS()
class PERSONA3REROAD_API UActionCommendsWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	UActionCommendsWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

private:
	
	//Button Click Event
	UFUNCTION()
	void OnAttackButtonClicked();

	UFUNCTION()
	void OnSkillButtonClicked();

	UFUNCTION()
	void OnGuardButtonClicked();

	UFUNCTION()
	void OnItemButtonClicked();

	UFUNCTION()
	void OnShiftButtonClicked();

	//Data Asset
	UPROPERTY()
	TObjectPtr<UActionCommendsWidgetDataAsset> WidgetDataAsset;

	//TMap
	UPROPERTY()
	TMap<EActionCommends, FButtonImagePair> BIPair;

	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite,Category = "Widget Animation",meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;
	

	//Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Guard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Shift;


	//Button
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> AttackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> SkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> GuardButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> SelectCommendSfx;
	
};
