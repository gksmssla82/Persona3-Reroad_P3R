// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "SkillListWidget.generated.h"

enum class EElement : uint8;

UENUM()
enum class  ESkillListAnimType : int8
{
	Reset,
	Create,
	CreateSelect,
	DownSelect,
	UpSelect,
	Hidden
};


class UHorizontalBox;
class UTextBlock;
class USkillListWidgetDataAsset;
class UWidgetAnimation;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API USkillListWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	USkillListWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Custom Function")
	void SetSkillInfo(const FName& InSkillType, const FName& InCostType, const int32& InCost, const FText& InText);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Function")
	void PlayWidgetAnim(const ESkillListAnimType& Anim);

	void SetSkillType(const EElement& InElement);
	
	void SetCostType(const FName& Name);
	
	void SetCost(const int32& Num);

	void SetSkillName(const FText& Text);


private:
	
	//Data Asset
	UPROPERTY()
	TObjectPtr<USkillListWidgetDataAsset> WidgetDataAsset;

	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Reset;
	
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateSelectAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> DownSelectAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> UpSelectAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Animations",
		meta = (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Hidden;

	//Image
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Image",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> CostColorBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Image",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> CostType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Image",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SkillType;

	//TextBlock
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget TextBlock",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> SkillName;

	//HorizontalBox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget UHorizontalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UHorizontalBox> SkillCostTextImageBox;
};
