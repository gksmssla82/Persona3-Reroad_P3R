// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UIData/BaseUIDataAsset.h"
#include "Structs/WidgetStructs.h"
#include "PartyPanelBattleDataAsset.generated.h"

//FSprite2D와 겹치지만 멤버 확장 가능성이 있어서 사용
USTRUCT(BlueprintType)
struct FPartyPanelBattleFaceGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Face")
	TObjectPtr<UPaperSprite> DefaultFace;

	UPROPERTY(EditAnywhere, Category = "Face")
	TObjectPtr<UPaperSprite> HitFace;
};


UCLASS()
class PERSONA3REROAD_API UPartyPanelBattleDataAsset : public UBaseUIDataAsset
{
	GENERATED_BODY()

public:
	UPartyPanelBattleDataAsset();

	FPartyPanelBattleFaceGroup* FindPartyFaceGroup(const FName Name);
	FSprite2D* FindStateText(const int32 Num);
	FLinearColor* FindColor(const FName Name);

private:
	UPROPERTY(EditAnywhere, Category = "FaceGroup")
	TMap<FName, FPartyPanelBattleFaceGroup> PartyFaceGroup;

	UPROPERTY(EditAnywhere, Category = "State Text")
	TMap<int32, FSprite2D> StateText;

	UPROPERTY(EditAnywhere, Category = "State Text")
	TMap<FName, FLinearColor> Color;
};
