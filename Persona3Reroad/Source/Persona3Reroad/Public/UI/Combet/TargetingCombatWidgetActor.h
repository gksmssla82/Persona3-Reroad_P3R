// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Combet/BaseCombatWidgetActor.h"
#include "TargetingCombatWidgetActor.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ATargetingCombatWidgetActor : public ABaseCombatWidgetActor
{
	GENERATED_BODY()
public:
	ATargetingCombatWidgetActor();

	virtual void BeginPlay() override;
	
	
	
};
