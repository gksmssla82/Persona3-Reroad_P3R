// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs//UVStruct.h"
#include "UIDataAsset.generated.h"

// DAY정보 저장중 사용 XX
// DAY정보 바꿀때 삭제꼭해야함
// DAY정보 바꿀때 삭제꼭해야함
// DAY정보 바꿀때 삭제꼭해야함
// DAY정보 바꿀때 삭제꼭해야함


/**
 * 
 */
UCLASS(BlueprintType)
class PERSONA3REROAD_API UUIDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(EditAnywhere, BlueprintType, Category = "Tag")

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UserWidget")
	TObjectPtr<UUserWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UV Group")
	TMap<FName,FUVInfo> UVInfo;
	
};
