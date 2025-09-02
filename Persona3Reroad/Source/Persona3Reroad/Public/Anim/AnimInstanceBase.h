// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
class ACharacterBase;
class UCharacterMovementComponent;
UCLASS()
class PERSONA3REROAD_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimInstanceBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;
	
	
	
	
};
