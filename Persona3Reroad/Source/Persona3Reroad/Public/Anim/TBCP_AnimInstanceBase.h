// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/AnimInstanceBase.h"
#include "TBCP_AnimInstanceBase.generated.h"

class UNiagaraComponent;
class UStatusComponent;
class ATBC_PlayerBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTBCP_AnimInstanceBase : public UAnimInstanceBase
{
	GENERATED_BODY()

public:
	UTBCP_AnimInstanceBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsBattleStart;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATBC_PlayerBase> TurnBasedCharacter;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsSelectCommend = false;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsSelectSKill = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsSturn = false;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsGuard = false;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsEvasion = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bIsSummon = false;
	
	
};
