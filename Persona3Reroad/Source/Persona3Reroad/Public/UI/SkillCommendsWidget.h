// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "SkillCommendsWidget.generated.h"

class URetainerBox;
class ATBC_PlayerBase;
class UTextBlock;
class UVerticalBox;
class USkillCommendsWidgetDataAsset;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API USkillCommendsWidget : public UBaseInputWidget
{
	GENERATED_BODY()

public:
	USkillCommendsWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void AddViewportEvent() override;
	
	void SetSkillCommends();

	void SetSkillInfo(const int32& Index);

	void SetPersonaImage(const FName& InName);
	

	UFUNCTION(BlueprintCallable, Category = "Custon Function")
	void PlayAnim_CreateSkillList();


private:

	void Input_UpStarted();
	void Input_DownStarted();
	void Input_ConfirmStarted();
	void Input_PersonaStatusStarted();
	void Input_CancelStared();





	//Data Asset
	UPROPERTY()
	TObjectPtr<USkillCommendsWidgetDataAsset> WidgetDataAsset;

	UPROPERTY()
	TObjectPtr<ATBC_PlayerBase> TurnOrder;

	//Widget Animation 
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Widget Animetions",
		meta = (BindWidgetAnim, AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> CreateAnim;

	//Widget Index
	UPROPERTY()
	int32 CurrentVerticalSkillListBoxIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> PersonaName;
	
	
	//VerticalSkillBox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> VerticalSkillListBox;
	
	//VerticalSkillDescriptionBox
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UVerticalBox> VerticalSkillDescriptionBox;

	//SkillDescriptionBox
	UPROPERTY()
	TArray<UTextBlock*> SkillDescriptionArray;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> SkillDescription_0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> SkillDescription_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> SkillDescription_2;

	//Persona Image
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UImage> PersonaBak;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> PersonaMaterials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget VerticalBox",
		meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<URetainerBox> PersonaRetainerBox;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> SelectSkillSfx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> SkillBackSfx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> SkillPickSfx;

	
	
};
