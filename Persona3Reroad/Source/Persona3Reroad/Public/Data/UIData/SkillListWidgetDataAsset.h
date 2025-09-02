// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "SkillListWidgetDataAsset.generated.h"


enum class EElement : uint8;

UCLASS()
class PERSONA3REROAD_API USkillListWidgetDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()
	USkillListWidgetDataAsset();

public:
	UPaperSprite* GetSkillCostSprite(const int32 Index);
	UPaperSprite* FindCostTypeSprite(const FName Name);
	FLinearColor* FindCostColor(const FName Name);
	UPaperSprite* FindSkillTypeSprite(const EElement& InElement);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillCost", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UPaperSprite>> SkillCostSpriteArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CostType", meta = (AllowPrivateAccess = true))
	TMap<FName, TObjectPtr<UPaperSprite>> CostTypeSpriteMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillCostColor", meta = (AllowPrivateAccess = true))
	TMap<FName, FLinearColor> CostColorMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillType", meta = (AllowPrivateAccess = true))
	TMap<EElement, TObjectPtr<UPaperSprite>> SkillTypeSpriteMap;
};
