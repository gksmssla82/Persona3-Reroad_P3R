// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/AnimInstance_Persona.h"

#include "Character/TurnBased/Persona/PersonaBase.h"

UAnimInstance_Persona::UAnimInstance_Persona(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UAnimInstance_Persona::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (IsValid(GetOwningActor()))
	{
		Persona = Cast<APersonaBase>(GetOwningActor());
	}
}

void UAnimInstance_Persona::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Persona))
	{
		bIsAttack = Persona->bIsAttack;
	}
}
