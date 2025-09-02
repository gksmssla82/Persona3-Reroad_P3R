// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProgressBarDataAsset.h"
#include "PaperSprite.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "MonsterProgressBarDataAsset.generated.h"

enum class EElement : uint8;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UMonsterProgressBarDataAsset : public UBaseProgressBarDataAsset
{
	GENERATED_BODY()

public:
	UPaperSprite* FindElementImage(const EElement& InElement);
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<EElement,TObjectPtr<UPaperSprite>> ElementImage;
	
};
