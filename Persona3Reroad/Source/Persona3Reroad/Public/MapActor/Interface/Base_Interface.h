// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Base_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UBase_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PERSONA3REROAD_API IBase_Interface
{
	GENERATED_BODY()
public:
	// 상호작용 동작 - 애니메이션 재생, 문 열기 등
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
