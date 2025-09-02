// Fill out your copyright notice in the Description page of Project Settings.


#include "System/WidgetInstanceSubsystem.h"

#include  "Blueprint/UserWidget.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "Data/PrimaryData/TagWidgetCountEntryDataAsset.h"
#include "Data/PrimaryData/TagWidgetPairPrimaryDataAsset.h"
#include "Data/PrimaryData/TargetControllerWidgetPrimaryDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "System/PersonaAssetManager.h"
#include "System/PersonaGameInstance.h"
#include "UI/BaseUIWidget.h"

void UWidgetInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UPersonaAssetManager& AssetManager = UPersonaAssetManager::Get();
	SetPersonaWidgetDataArray(AssetManager.LoadWidgetSoftClass());
	
}

void UWidgetInstanceSubsystem::SetPersonaWidgetDataArray(
	const TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>>& InPersonaWidgetDataArray)
{
	PersonaWidgetDataArray = InPersonaWidgetDataArray;
	
}

void UWidgetInstanceSubsystem::CreateWidget()
{
	ClearWidget();
	
	for (int32 i = 0; i < PersonaWidgetDataArray.Num(); i++)
	{
		if (PersonaWidgetDataArray[i]->GetWidgetEnumName() == EWidgetName::TargetController)
		{
			continue;
		}
		if (PersonaWidgetDataArray[i]->GetWidgetEnumName() == EWidgetName::Combat)
		{
			SetTagWidgetCountEntry(PersonaWidgetDataArray[i],CombatWidgetMap);
		}
		else
		{
			SetTagWidgetPair(PersonaWidgetDataArray[i],RegistryWidgetMap);
		}
	}
}

void UWidgetInstanceSubsystem::ClearWidget()
{
	//Stack Clear
	ClearWidgetStack();

	//Current Level Widget Array Clear
	for (auto& Iter :CurrentLevelWidgetArray)
	{
		Iter->RemoveFromParent();
	}
	CurrentLevelWidgetArray.Reset();
	
	//Registry Widget Map Clear
	for (auto& Iter :RegistryWidgetMap)
	{
		if (UBaseUIWidget* Widget = Iter.Value)
		{
			Widget->RemoveFromParent(); 
		}
	}
	RegistryWidgetMap.Reset();

	//Combat Widget Map Clear
	for (auto& Iter :CombatWidgetMap)
	{
		for (auto& WidgetArray : Iter.Value.Widgets)
		{
			WidgetArray->RemoveFromParent();
		}
	}
	CombatWidgetMap.Reset();
}

void UWidgetInstanceSubsystem::ClearWidgetStack()
{
	//Stack Clear
	for (auto& Iter :WidgetStack)
	{
		Iter->RemoveViewportEvent();
	}
	WidgetStack.Reset();
}

void UWidgetInstanceSubsystem::PushWidget(UBaseUIWidget* InWidget)
{
	if (InWidget)
	{
		if (WidgetStack.Num() > 0)
		{
			if (UBaseUIWidget* MakeLastWidget = WidgetStack.Last())
			{
				MakeLastWidget->RemoveViewportEvent();
			}
		}
		InWidget->AddViewportEvent();
		WidgetStack.Add(InWidget);
	}
}

void UWidgetInstanceSubsystem::PopWidget()
{
	if (WidgetStack.Num() > 0)
	{
		if (UBaseUIWidget* MakePopWidget = WidgetStack.Pop())
		{
			MakePopWidget->RemoveViewportEvent();
		}
		if (WidgetStack.Num() > 0)
		{
			if (UBaseUIWidget* MakeLastWidget = WidgetStack.Last())
			{
				MakeLastWidget->AddViewportEvent();
			}
		}
	}
}

UBaseUIWidget* UWidgetInstanceSubsystem::GetStackLastWidget()
{
	if (WidgetStack.Num() > 0)
	{
		return WidgetStack.Last();
	}
	return nullptr;
}

void UWidgetInstanceSubsystem::AddTransitionWidget(UBaseUIWidget* InWidget)
{
	if(InWidget)
	{
		TransitionWidgetArray.Add(InWidget);
	}
}

void UWidgetInstanceSubsystem::ClearTransitionWidget()
{
	for (auto& Iter :TransitionWidgetArray)
	{
		Iter->RemoveViewportEvent();
	}
	WidgetStack.Reset();
	
}

void UWidgetInstanceSubsystem::AddFromCurrenLevelWidgetArray(UBaseUIWidget* InWidget)
{
	if (InWidget)
	{
		CurrentLevelWidgetArray.Add(InWidget);
	}
}


TArray<UBaseUIWidget*> UWidgetInstanceSubsystem::GetCurrentLevelWidgetArray() const
{
	return CurrentLevelWidgetArray;
}

void UWidgetInstanceSubsystem::AddViewportEventCurrentLevelWidgetArray()
{
	for (int32 i = 0; i < CurrentLevelWidgetArray.Num(); i++)
	{
		CurrentLevelWidgetArray[i]->AddViewportEvent();
	}
}

void UWidgetInstanceSubsystem::RemoveViewportEventCurrentLevelWidgetArray()
{
	for (int32 i = 0; i < CurrentLevelWidgetArray.Num(); i++)
	{
		CurrentLevelWidgetArray[i]->RemoveViewportEvent();
	}
}

void UWidgetInstanceSubsystem::CreateTargetController()
{
	if (PersonaWidgetDataArray.Num() > 0)
	{
		for (int32 i = 0; i < PersonaWidgetDataArray.Num(); i++)
		{
			if (PersonaWidgetDataArray[i]->GetWidgetEnumName() == EWidgetName::TargetController)
			{
				if (UTargetControllerWidgetPrimaryDataAsset* MakeDataAsset =
					Cast<UTargetControllerWidgetPrimaryDataAsset>(PersonaWidgetDataArray[i]))
				{
					AActor* MakeActor = GetWorld()->SpawnActor(MakeDataAsset->GetTagCombatPair().Combat);
					TargetController = Cast<ATargetingCombatWidgetActor>(MakeActor);
					break;
				}
			}
		}
	}
}

UBaseUIWidget* UWidgetInstanceSubsystem::FindRegistryWidgetMap(const FGameplayTag InTag) const
{
	if (UBaseUIWidget* MakeWidget = RegistryWidgetMap.Find(InTag)->Get())
	{
		return MakeWidget;
	}
	return nullptr;
}

TArray<UBaseUIWidget*> UWidgetInstanceSubsystem::FindCombatWidgetMap(const FGameplayTag InTag)
{
	
	if (FWidgetArray* MakeWidgetArray = CombatWidgetMap.Find(InTag))
	{
		return MakeWidgetArray->Widgets;
	}
		return {};
}

void UWidgetInstanceSubsystem::SetTagWidgetPair(const TObjectPtr<UBaseWidgetPrimaryDataAsset>& InWidgetData,
                                                TMap<FGameplayTag, TObjectPtr<UBaseUIWidget>>& InWidgetMap)
{

	if (UPersonaGameInstance* MakeGameInstance = Cast<UPersonaGameInstance>(GetGameInstance()))
	{
		if (UTagWidgetPairPrimaryDataAsset* MakeWidgetData = Cast<UTagWidgetPairPrimaryDataAsset>(InWidgetData))
		{
			TArray<FTagWidgetPair> MakeWidgetArray = MakeWidgetData->GetTagWidgetPairArray();
			for (int32 i = 0; i < MakeWidgetArray.Num(); i++)
			{
				TSubclassOf<UBaseUIWidget> MakeSubclass = MakeWidgetArray[i].Widget;
				UBaseUIWidget* MakeWidget = ::CreateWidget<UBaseUIWidget>(MakeGameInstance,MakeSubclass);
				InWidgetMap.Add(MakeWidgetArray[i].Tag,MakeWidget);
			}
		}
	}
}

void UWidgetInstanceSubsystem::SetTagWidgetCountEntry(const TObjectPtr<UBaseWidgetPrimaryDataAsset>& InWidgetData,
                                                      TMap<FGameplayTag, FWidgetArray>& InWidgetMap)
{
	if (UTagWidgetCountEntryDataAsset* MakeWidgetData = Cast<UTagWidgetCountEntryDataAsset>(InWidgetData))
	{
		TArray<FTagWidgetCountEntry> MakeArray = MakeWidgetData->GetTagWidgetCountEntry();
		UPersonaGameInstance* MakeGameInstance = Cast<UPersonaGameInstance>(GetGameInstance());

		for (FTagWidgetCountEntry Iter : MakeArray)
		{
			TArray<TObjectPtr<UBaseUIWidget>> MakeWidgetArray;
			for (int i = 0; i < Iter.CountEntry; i++)
			{
				TObjectPtr<UBaseUIWidget> MakeWidget = ::CreateWidget<UBaseUIWidget>(MakeGameInstance,Iter.Widget);
				MakeWidgetArray.Add(MakeWidget);
			}
			InWidgetMap.Add(Iter.Tag, FWidgetArray(MakeWidgetArray));
		}
	}
}




