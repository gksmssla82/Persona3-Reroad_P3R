// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UI/BaseUIWidget.h"
#include "UI/Combet/BaseCombatWidgetActor.h"
#include "BaseWidgetPrimaryDataAsset.generated.h"


UENUM()
enum class EWidgetName
{
	Global,
	KeyHelper,
	Transition,
	Combat,
	Title,
	Battle,
	Daily,
	TargetController
};

USTRUCT(BlueprintType)
struct FTagWidgetPair
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TagWidgetPair")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "TagWidgetPair")
	TSubclassOf<UBaseUIWidget> Widget;

	FTagWidgetPair()
		: Tag()
		  , Widget(nullptr)
	{
	}

	FTagWidgetPair(const FGameplayTag InTag, const TSubclassOf<UBaseUIWidget>& InWidget)
		: Tag(InTag)
		  , Widget(InWidget)
	{
	}
};

USTRUCT(BlueprintType)
struct FTagWidgetCountEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "FTagWidgetCountEntry")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "FTagWidgetCountEntry")
	TSubclassOf<UBaseUIWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "FTagWidgetCountEntry")
	int32 CountEntry;

	FTagWidgetCountEntry()
		: Tag()
		  , Widget(nullptr)
		  , CountEntry(0)
	{
	}

	FTagWidgetCountEntry(const FGameplayTag InTag, const TSubclassOf<UBaseUIWidget>& InWidget, const int32 InCountEntry)
		: Tag(InTag)
		  , Widget(InWidget)
		  , CountEntry(InCountEntry)
	{
	}
};

USTRUCT(BlueprintType)
struct FTagCombatPair
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TagWidgetPair")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "TagWidgetPair")
	TSubclassOf<ABaseCombatWidgetActor> Combat;

	FTagCombatPair()
		: Tag()
		  , Combat(nullptr)
	{
	}

	FTagCombatPair(const FGameplayTag InTag, const TSubclassOf<ABaseCombatWidgetActor>& InWidget)
		: Tag(InTag)
		  , Combat(InWidget)
	{
	}
};


//class UBaseUIWidget;
/**
 * 
 */
UCLASS(BlueprintType)
class PERSONA3REROAD_API UBaseWidgetPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
	FORCEINLINE EWidgetName GetWidgetEnumName() const { return WidgetEnumName; } ;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Widget", GetFName());
	}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Asset Name", meta = (AllowPrivateAccess = true))
	EWidgetName WidgetEnumName;
};
