// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePartyPanelWidget.h"
#include "Structs/WidgetStructs.h"
#include "PartyPanelBattleWidget.generated.h"

UENUM(BlueprintType)
enum class EPartyPanelBattleAnimType : uint8
{
	Create,
	InTurnOrder,
	OutTurnOrder,
	Hit,
	Hidden
};

class ATBC_PlayerBase;
class UPartyPanelBattleDataAsset;
class UPaperSprite;


UCLASS()
class PERSONA3REROAD_API UPartyPanelBattleWidget : public UBasePartyPanelWidget
{
	GENERATED_BODY()

public:
	UPartyPanelBattleWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	void Init_PartyPanelBattle(const TObjectPtr<ATBC_PlayerBase>& InOwner);

	void PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType AnimType);
	
	UFUNCTION()
	void UpdateTextStatus();
	UFUNCTION()
	void UpdateStatusBar();
	
	void SetFace(UPaperSprite* Sprite);
	void SetDefaultFace();
	void SetHitFace();

	//Bind Function
	UFUNCTION()
	void OnHitEvent();

	UFUNCTION()
	void InTurnOrderEvent();

	UFUNCTION()
	void OutTurnOrderEvent();
	
	UFUNCTION(BlueprintCallable, Category = "PartyPanelBattle")
	void HitAnimStart();
	
	UFUNCTION(BlueprintCallable, Category = "PartyPanelBattle")
	void HitAnimEnd();

private:

	//Set Owner
	UPROPERTY()
	TObjectPtr<ATBC_PlayerBase> OwnerCharacter;
	
	//Data Asset
	UPROPERTY()
	TObjectPtr<UPartyPanelBattleDataAsset> WidgetDataAsset;

	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> InTurnOrder;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> OutTurnOrder;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> HitAnim;

	UPROPERTY(Transient,BlueprintReadWrite,meta  = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Hidden;
	
	

	//Face Image
	UPROPERTY()
	FUImage3D FaceGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> Face;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> FaceShadowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> FaceShadowRight;


	//HP Text IMage
	UPROPERTY()
	TArray<FUImage2D> HPTextImageGroup;


	//State Text Image HP100s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_100sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_100sPlaceOutline;


	//State Text Image HP10s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_10sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_10sPlaceOutline;


	//State Text Image HP1s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_1sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> HPText_1sPlaceOutline;


	//SP Text IMage
	TArray<FUImage2D> SPTextImageGroup;

	//State Text Image SP100s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_100sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_100sPlaceOutline;


	//State Text Image HP10s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_10sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_10sPlaceOutline;


	//State Text Image HP1s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_1sPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> SPText_1sPlaceOutline;
};
