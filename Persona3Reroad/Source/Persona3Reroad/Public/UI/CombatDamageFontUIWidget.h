// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "CombatDamageFontUIWidget.generated.h"

class UCombatDamageFontDataAsset;

UENUM()
enum class ECombatDamageFontAnimType : uint8
{
	Create,
	Reset
};

UCLASS()
class PERSONA3REROAD_API UCombatDamageFontUIWidget : public UBaseUIWidget
{
	GENERATED_BODY()
public:
	
	UCombatDamageFontUIWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	void Init_DamageFont(int32 InNumber ,bool Weak);

	void PlayDamageFontAnimation(ECombatDamageFontAnimType AnimType);

private:
	void SetDamageBakColor();
	//Data Asset
	UPROPERTY()
	TObjectPtr<UCombatDamageFontDataAsset> WidgetDataAsset;

	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Damage Font",
		meta = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Damage Font",
		meta = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Reset;

	//Widget Damage Image
	UPROPERTY()
	FUImage2D Damage2D;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage Font",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage Font",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> DamageBak;
};
