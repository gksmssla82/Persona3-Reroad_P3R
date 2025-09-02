// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PersonaAssetData.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FName AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AssetLabels;
};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;
};

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPersonaAssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	
public:
	FSoftObjectPath GetAssetPathByName(const FName& AssetName);
	const FAssetSet& GetAssetSetByLabel(const FName& Label);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName,FAssetSet> AssetGroupNameToSet;

	// 에셋 이름으로 경로 가져옴
	UPROPERTY()
	TMap<FName, FSoftObjectPath> AssetNameToPath;

	// 라벨로 에셋 항목 가져옴
	UPROPERTY()
	TMap<FName, FAssetSet> AssetLabelToSet;
};
