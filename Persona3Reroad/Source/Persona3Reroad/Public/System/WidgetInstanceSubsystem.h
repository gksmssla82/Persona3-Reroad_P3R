// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/BaseUIWidget.h"
#include "UI/Combet/TargetingCombatWidgetActor.h"
#include "WidgetInstanceSubsystem.generated.h"



USTRUCT(BlueprintType)
struct FWidgetArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UBaseUIWidget>> Widgets;

	FWidgetArray()
		: Widgets()
	{
	}

	FWidgetArray(const TArray<TObjectPtr<UBaseUIWidget>>& InWidgets)
		: Widgets(InWidgets)
	{
	}
};

UCLASS()
class PERSONA3REROAD_API UWidgetInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//Set Primary Data
	void SetPersonaWidgetDataArray(const TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>>& InPersonaWidgetDataArray);

	//Create Clear Widget
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void CreateWidget();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void ClearWidget();
	
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void ClearWidgetStack();

	//Widget Push Pop
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void PushWidget(UBaseUIWidget* InWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void PopWidget();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	UBaseUIWidget* GetStackLastWidget();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void AddTransitionWidget(UBaseUIWidget* InWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void ClearTransitionWidget();

	//Current WidgetArray
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void AddFromCurrenLevelWidgetArray(UBaseUIWidget* InWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	TArray<UBaseUIWidget*> GetCurrentLevelWidgetArray() const;

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void AddViewportEventCurrentLevelWidgetArray();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void RemoveViewportEventCurrentLevelWidgetArray();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	void CreateTargetController();

	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	FORCEINLINE ATargetingCombatWidgetActor* GetTargetController() const {return TargetController;}

	//Find Registry Widget Map
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	UBaseUIWidget* FindRegistryWidgetMap(const FGameplayTag InTag) const;

	//Find Combat Widget Map
	UFUNCTION(BlueprintCallable, Category = "WidgetInstanceSubsystem")
	TArray<UBaseUIWidget*> FindCombatWidgetMap(const FGameplayTag InTag);
	

private:
	
	void SetTagWidgetPair(const TObjectPtr<UBaseWidgetPrimaryDataAsset>& InWidgetData,
	                      TMap<FGameplayTag, TObjectPtr<UBaseUIWidget>>& InWidgetMap);
	
	void SetTagWidgetCountEntry(const TObjectPtr<UBaseWidgetPrimaryDataAsset>& InWidgetData,
						  TMap<FGameplayTag, FWidgetArray>& InWidgetMap);

	//Widget Data
	UPROPERTY()
	TArray<TObjectPtr<UBaseWidgetPrimaryDataAsset>> PersonaWidgetDataArray;

	//Widget Stack
	UPROPERTY(BlueprintReadWrite, category = "WidgetStack", meta = (Allowprivateaccess = true))
	TArray<TObjectPtr<UBaseUIWidget>> WidgetStack;

	UPROPERTY(BlueprintReadWrite, category = "CurrentLevelWidget", meta = (Allowprivateaccess = true))
	TArray<TObjectPtr<UBaseUIWidget>> CurrentLevelWidgetArray;
	
	//Widget Map
	UPROPERTY(BlueprintReadWrite, category = "Registry", meta = (Allowprivateaccess = true))
	TMap<FGameplayTag, TObjectPtr<UBaseUIWidget>> RegistryWidgetMap;

	UPROPERTY(BlueprintReadWrite, category = "Transition", meta = (Allowprivateaccess = true))
	TArray<TObjectPtr<UBaseUIWidget>> TransitionWidgetArray;
	
	//Widget Combat
	UPROPERTY(BlueprintReadWrite,category = "Combat",meta = (Allowprivateaccess = true))
	TMap<FGameplayTag, FWidgetArray> CombatWidgetMap;

	//Target Controller
	UPROPERTY(BlueprintReadWrite,category = "Target Controller",meta = (Allowprivateaccess = true))
	TObjectPtr<ATargetingCombatWidgetActor> TargetController;

};
