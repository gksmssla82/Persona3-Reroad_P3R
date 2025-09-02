// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "data/PersonaAssetData.h"
#include "PersonaAssetManager.generated.h"

class UBaseWidgetPrimaryDataAsset;
class UPersonaAssetData;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPersonaAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UPersonaAssetManager();

	static UPersonaAssetManager& Get();

public:
	static void Initialize();

	template<typename  AssetType>
	static AssetType* GetAssetByName(const FName& AssetName);

	// 동기 로드
	static void LoadSyncByPath(const FSoftObjectPath& AssetPath);
	static void LoadSyncByName(const FName& AssetName);
	static void LoadSyncByLabel(const FName& Label);

	static void ReleaseByPath(const FSoftObjectPath& AssetPath);
	static void ReleaseByName(const FName& AssetName);
	static void ReleaseByLabel(const FName& Label);
	static void ReleaseAll();

	//Widget 로드
	static TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>> LoadWidgetSoftClass();
	

private:
	void LoadPreloadAssets();
	void AddLoadedAsset(const FName& AssetName, const UObject* Asset);

private:
	UPROPERTY()
	TObjectPtr<UPersonaAssetData> LoadedAssetData;

	UPROPERTY()
	TMap<FName, TObjectPtr<const UObject>> NameToLoadedAsset;

	//FCriticalSection LoadedAssetsCritical; 뮤텍스 락

	
};

template <typename AssetType>
AssetType* UPersonaAssetManager::GetAssetByName(const FName& AssetName)
{
	UPersonaAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	if (AssetPath.IsValid())
	{
		LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());

		if (LoadedAsset == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted sync Loading Because Asset Had't Loaded yet [%s]"), *AssetPath.ToString());
			LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
		}
	}
	return LoadedAsset;

	//헤응
}

