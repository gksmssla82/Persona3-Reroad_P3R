// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/AnimInstanceBase.h"
#include "TBCE_AnimInstanceBase.generated.h"

/**
 * 
 */

class ATBC_EnemyBase;
class UStatusComponent;

UCLASS()
class PERSONA3REROAD_API UTBCE_AnimInstanceBase : public UAnimInstanceBase
{
	GENERATED_BODY()

public:
	UTBCE_AnimInstanceBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATBC_EnemyBase> TurnBasedCharacter;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStatusComponent> StatusComponent;

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsSturn = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsDead = false;
	
};
