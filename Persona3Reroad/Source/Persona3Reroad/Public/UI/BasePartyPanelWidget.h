// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseUIWidget.h"
#include "BasePartyPanelWidget.generated.h"

class UPartyPanelBattleDataAsset;
class UProgressBar;
class UImage;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UBasePartyPanelWidget : public UBaseUIWidget
{
	GENERATED_BODY()
	
public:
	
	UBasePartyPanelWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	void SetHPBarPercent(const float MaxHP, const float CurrentHP);
	void SetSPBarPercent(const float MaxSP, const float CurrentSP);
	
	
protected:
	
	//State Bar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget,AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> HPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget,AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> SPBar;
	

};
