// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "SkillCommendsWidgetDataAsset.generated.h"

class USkillListWidget;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API USkillCommendsWidgetDataAsset : public UBaseInputWidgetDataAsset
{
	GENERATED_BODY()
public:
	FLinearColor* GetSkillDescriptionColor();
	
	UFont* GetSkillDescriptionFont();
	
	TSubclassOf<USkillListWidget> GetSkillListWidgetClass();

	UTexture2D* FindPersonaTexture(const FName& InPersonaName);
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WBP_SkillList",meta = (AllowPrivateAccess = true))
	TSubclassOf<USkillListWidget> SkillListWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color",meta = (AllowPrivateAccess = true))
	FLinearColor SkillDescriptionColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Font",meta = (AllowPrivateAccess = true))
	UFont* SkillDescriptionFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Persona Texture",meta = (AllowPrivateAccess = true))
	TMap<FName,TObjectPtr<UTexture2D>> PersonaTextureTMap;
	
};
