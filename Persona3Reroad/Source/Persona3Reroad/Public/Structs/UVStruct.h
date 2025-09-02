// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "UVStruct.generated.h"


USTRUCT(BlueprintType)
struct FUVData : public FTableRowBase

{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UV Data")
	FVector2D Offset;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UV Data")
	FVector2D Size;
};


USTRUCT(BlueprintType)
struct FUVInfo

{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UV Info")
	TObjectPtr<UTexture2D> Texture;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UV Info")
	TMap<FName, TObjectPtr<UDataTable>> UVDataTable;
};
