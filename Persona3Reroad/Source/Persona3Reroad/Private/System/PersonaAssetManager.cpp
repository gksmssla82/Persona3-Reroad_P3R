// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PersonaAssetManager.h"

#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"

UPersonaAssetManager::UPersonaAssetManager()
{
}

UPersonaAssetManager& UPersonaAssetManager::Get()
{
	if (UPersonaAssetManager* Singleton = Cast<UPersonaAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}
	
	return *NewObject<UPersonaAssetManager>();
}

void UPersonaAssetManager::Initialize()
{
	// TODO Asset Load
	Get().LoadPreloadAssets();
	
}

void UPersonaAssetManager::LoadSyncByPath(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		UObject* LoadedAsset = AssetPath.ResolveObject();

		if (LoadedAsset == nullptr)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
			}
			else
			{
				LoadedAsset = AssetPath.TryLoad();
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAsset(AssetPath.GetAssetFName(), LoadedAsset);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed to Load Asset [%s]"), *AssetPath.ToString());
		}
		
	}

	
}

void UPersonaAssetManager::LoadSyncByName(const FName& AssetName)
{
	UPersonaAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(AssetName);
	LoadSyncByPath(AssetPath);
}

void UPersonaAssetManager::LoadSyncByLabel(const FName& Label)
{
	if (UAssetManager::IsInitialized() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be Initalized"));
		return;
	}

	UPersonaAssetData* AssetData = Get().LoadedAssetData;
	
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;

	const FAssetSet& AssetSet = AssetData->GetAssetSetByLabel(Label);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadSyncByPath(AssetPath);

		if (AssetPath.IsValid())
		{
			AssetPaths.Emplace(AssetPath);
		}
	}

	GetStreamableManager().RequestSyncLoad(AssetPaths);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;

		if (AssetPath.IsValid())
		{
			if (UObject* LoadedAsset = AssetPath.ResolveObject())
			{
				Get().AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Failed to Load Asset [%s]"), *AssetPath.ToString());
			}
		}
	}
		
}

void UPersonaAssetManager::ReleaseByPath(const FSoftObjectPath& AssetPath)
{
	FName AssetName = AssetPath.GetAssetFName();
	ReleaseByName(AssetName);
}

void UPersonaAssetManager::ReleaseByName(const FName& AssetName)
{
	UPersonaAssetManager& AssetManager = Get();

	if (AssetManager.NameToLoadedAsset.Contains(AssetName))
	{
		AssetManager.NameToLoadedAsset.Remove(AssetName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't Find Loaded Asset By AssetName [%s]."), *AssetName.ToString());
	}
}

void UPersonaAssetManager::ReleaseByLabel(const FName& Label)
{
	UPersonaAssetManager& AssetManager = Get();
	UPersonaAssetData* LoadedAssetData = AssetManager.LoadedAssetData;
	const FAssetSet& AssetSet = LoadedAssetData->GetAssetSetByLabel(Label);

	for (const FAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FName& AssetName = AssetEntry.AssetName;

		if (AssetManager.NameToLoadedAsset.Contains(AssetName))
		{
			AssetManager.NameToLoadedAsset.Remove(AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Can't Find Loaded Asset By AssetLabel [%s]"), *Label.ToString());
		}
	}
}

void UPersonaAssetManager::ReleaseAll()
{
	UPersonaAssetManager& AssetManager = Get();
	AssetManager.NameToLoadedAsset.Reset();
}

TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>> UPersonaAssetManager::LoadWidgetSoftClass()
{
	FPrimaryAssetType WidgetAssetType("Widget");
	TArray<FPrimaryAssetId> AssetIdList;
	Get().GetPrimaryAssetIdList(WidgetAssetType, AssetIdList);

	TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>> PersonaWidgetDataArray;

	for (const FPrimaryAssetId& AssetId : AssetIdList)
	{
		FSoftObjectPath AssetPath = Get().GetPrimaryAssetPath(AssetId);
		if (UObject* LoadedObject = Get().StreamableManager.LoadSynchronous(AssetPath))
		{
			if (UClass* LoadedClass = Cast<UClass>(LoadedObject))
			{
				if (TObjectPtr<UBaseWidgetPrimaryDataAsset> PDA = Cast<UBaseWidgetPrimaryDataAsset>(
					LoadedClass->GetDefaultObject()))
				{
					// const UEnum* EnumPtr = StaticEnum<EWidgetName>();
					// FString StateName = EnumPtr->GetNameStringByValue(static_cast<int64>(PDA->GetWidgetEnumName()));
					// UE_LOG(LogTemp,Warning,TEXT("%s"), *StateName);

					PersonaWidgetDataArray.Add(PDA);
				}
			}
		}
	}
	return PersonaWidgetDataArray;
}

void UPersonaAssetManager::LoadPreloadAssets()
{
	if (LoadedAssetData)
		return;

	UPersonaAssetData* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UPersonaAssetData::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);

	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UPersonaAssetData>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		//Pro
		LoadedAssetData = AssetData;
		LoadSyncByLabel("Preload");
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to Load AssetData Asset Type [%s]"), *PrimaryAssetType.ToString());
	}
	
}

void UPersonaAssetManager::AddLoadedAsset(const FName& AssetName, const UObject* Asset)
{
	if (AssetName.IsValid() && Asset)
	{
		// 뮤텍스 락
		//FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		if (NameToLoadedAsset.Contains(AssetName) == false)
		{
			NameToLoadedAsset.Add(AssetName, Asset);
		}
	}
}
