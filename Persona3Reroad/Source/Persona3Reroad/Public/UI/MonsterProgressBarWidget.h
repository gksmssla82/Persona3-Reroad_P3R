// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseProgressBarWidget.h"
#include "MonsterProgressBarWidget.generated.h"

enum class EElement : uint8;
class UMonsterProgressBarDataAsset;
class ATBC_EnemyBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UMonsterProgressBarWidget : public UBaseProgressBarWidget
{
	GENERATED_BODY()

public:
	UMonsterProgressBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void Init_ProgressBar(const TObjectPtr<ATBC_CharacterBase>& InOwner) override;

	void SetElementType(EElement InElement);

private:
	
	UPROPERTY()
	TObjectPtr<UMonsterProgressBarDataAsset> WidgetDataAsset;

	//Attack Type Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UImage> AttackType;
	
};
