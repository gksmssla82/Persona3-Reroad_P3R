// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BaseProgressBarWidget.generated.h"

class UBaseFloatingWidget;
class UCanvasPanel;
class UBaseProgressBarDataAsset;
class ATBC_CharacterBase;
class ATBC_PlayerBase;

UENUM(BlueprintType)
enum class EProgressBarAnimType :uint8
{
	Reset,
	Create,
	Hit,
	Weak,
	Critical,
	Miss
};

class UProgressBar;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBaseProgressBarWidget : public UBaseUIWidget
{
	GENERATED_BODY()

public:
	UBaseProgressBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	virtual void Init_ProgressBar(const TObjectPtr<ATBC_CharacterBase>& InOwner);
	virtual void PlayProgressAnimation(EProgressBarAnimType InProgressBarAnimType);

	
protected:

	UFUNCTION()
	virtual void OnHitEvent(int32 Damage);
	
	UFUNCTION()
	virtual void OnWeakEvent();

	UFUNCTION()
	virtual void OnCriticalEvent();

	UFUNCTION()
	virtual void OnResistEvent();
	
	UFUNCTION()
	virtual void OnMissEvent();
	
	UFUNCTION()
	virtual void OnTurnEndEvent();
	
	void UpdateHPBar();
	void UpdateHPBarRate();

	UPROPERTY()
	bool bIsWeak;

	UPROPERTY()
	TObjectPtr<UBaseProgressBarDataAsset> BaseWidgetDataAsset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ProgressBar",meta=(AllowPrivateAccess=true))
	TObjectPtr<ATBC_CharacterBase> WidgetOwner;

	//Widget Animation
	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> Reset;

	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> HitAnim;

	UPROPERTY(Transient, BlueprintReadWrite, Category="UBaseProgressBarWidget",
	meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> MissAnim;

	//ProgressBar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UProgressBar> HPBarRate;

	//Root Damage Group
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> RootDamageGroup;

	//Floating Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UBaseFloatingWidget> Resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UBaseFloatingWidget> Miss;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UBaseFloatingWidget> Critical;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UBaseProgressBarWidget",
		meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UBaseFloatingWidget> Weak;

	
	
	
};
