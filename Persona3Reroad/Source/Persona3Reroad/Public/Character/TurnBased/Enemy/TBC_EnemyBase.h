// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "TBC_EnemyBase.generated.h"

/**
 * 
 */

class USkillBase;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PERSONA3REROAD_API ATBC_EnemyBase : public ATBC_CharacterBase
{
	GENERATED_BODY()
	
public:
	ATBC_EnemyBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void OnDeath() override;


	virtual void Set_Enemy_RotationFromAxis();

private:
	UPROPERTY(EditAnywhere, Category=Sound)
	TObjectPtr<USoundBase> SpawnSound;
	
};
