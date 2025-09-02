// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PersonaAssetData.h"
#include "UObject/ObjectSaveContext.h"

void UPersonaAssetData::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
	// PDA_AssetData를 Save하면 자동으로 실행
	Super::PreSave(ObjectSaveContext);

	// Map 지움
	AssetNameToPath.Empty();
	AssetLabelToSet.Empty();

	AssetGroupNameToSet.KeySort([](const FName& A, const FName& B)
	{
		return (A.Compare(B) < 0);
	});

	for (const auto& Pair : AssetGroupNameToSet)
	{
		const FAssetSet& AssetSet = Pair.Value;
		for (FAssetEntry AssetEntry : AssetSet.AssetEntries)
		{
			FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
			
			// const FString& AssetName = AssetPath.GetAssetName();
			// if (AssetName.StartsWith(TEXT("BP_")) || AssetName.StartsWith(TEXT("B_")) || 
	  //           AssetName.StartsWith(TEXT("GE_")) || AssetName.StartsWith(TEXT("GA_")))
			// {
			// 	FString AssetPathString = AssetPath.GetAssetPathString();
			// 	AssetPathString.Append(TEXT("_C"));
			// 	AssetPath = FSoftObjectPath(AssetPathString);
			// }

			AssetNameToPath.Emplace(AssetEntry.AssetName, AssetEntry.AssetPath);

			for (const FName& Label : AssetEntry.AssetLabels)
			{
				AssetLabelToSet.FindOrAdd(Label).AssetEntries.Emplace(AssetEntry);
			}
		}
	}
}

FSoftObjectPath UPersonaAssetData::GetAssetPathByName(const FName& AssetName)
{
	FSoftObjectPath* AssetPath = AssetNameToPath.Find(AssetName);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't Find Asset Path From Asset Name [%s]."), *AssetName.ToString());
	return *AssetPath;
}

const FAssetSet& UPersonaAssetData::GetAssetSetByLabel(const FName& Label)
{
	const FAssetSet* AssetSet = AssetLabelToSet.Find(Label);
	ensureAlwaysMsgf(AssetSet, TEXT("Can't Find Asset Set From Label [%s]."), *Label.ToString());
	return *AssetSet;
}
