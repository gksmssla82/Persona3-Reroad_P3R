// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/AnimInstanceBase.h"
#include "AnimInstance_Persona.generated.h"

class APersonaBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimInstance_Persona : public UAnimInstanceBase
{
	GENERATED_BODY()

public:
	UAnimInstance_Persona(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	TObjectPtr<APersonaBase> Persona;
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttack;
	
};
