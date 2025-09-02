// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimInstanceBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimInstanceBase::UAnimInstanceBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	Character = Cast<ACharacter>(TryGetPawnOwner());
	
	if (Character)
		MovementComponent = Character->GetCharacterMovement();
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	

	if (IsValid(MovementComponent))
	{
		Velocity = MovementComponent->Velocity;
	
		GroundSpeed = Velocity.Size2D();

		bShouldMove = (GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	}
}
