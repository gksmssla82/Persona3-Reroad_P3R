// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BasePartyPanelWidget.h"
#include "PartyPanelFieldWidget.generated.h"

class UPartyPanelFieldDataAsset;
class ATBC_PlayerBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPartyPanelFieldWidget : public UBasePartyPanelWidget
{
	GENERATED_BODY()
public:
	UPartyPanelFieldWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	virtual void RemoveViewportEvent() override;

	void Init_PartyPanelBattle(const TObjectPtr<ATBC_PlayerBase>& InOwner);

	void UpdateStatusBar();
	
private:

	//Set Owner
	UPROPERTY()
	TObjectPtr<ATBC_PlayerBase> OwnerCharacter;
	
	//Data Asset
	UPROPERTY()
	TObjectPtr<UPartyPanelFieldDataAsset> WidgetDataAsset;
	
	UPROPERTY()
	FUImage3D FaceGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> FaceShadowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> FaceShadowRight;
	
};
