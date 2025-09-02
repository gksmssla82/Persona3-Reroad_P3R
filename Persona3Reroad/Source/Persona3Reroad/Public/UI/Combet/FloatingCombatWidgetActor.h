// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Combet/BaseCombatWidgetActor.h"
#include "FloatingCombatWidgetActor.generated.h"

class UCombatDamageGroupWidget;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API AFloatingCombatWidgetActor : public ABaseCombatWidgetActor
{
	GENERATED_BODY()
public:
	AFloatingCombatWidgetActor();

	virtual void PostInitializeComponents() override;

	void Init_DamageGroup(const int32& InDamage, const bool& Weak = false);


protected:
	virtual void BeginPlay() override;

private:

	TObjectPtr<UCombatDamageGroupWidget> CombatWidget;
	


	
};
