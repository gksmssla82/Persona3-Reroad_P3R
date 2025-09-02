// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enum/EnumBase.h"
#include "Object/PatrolRoute.h"
#include "AIInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PERSONA3REROAD_API IAIInterface
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement")
	float SetMovementSpeed(EMovementSpeed MovementSpeed);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Patrol")
	APatrolRoute* GetPatrolRoute();
};
