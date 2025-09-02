// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyStateBackStep.h"
#include "Components/TurnComponent.h"

UAnimNotifyStateBackStep::UAnimNotifyStateBackStep()
{
}

void UAnimNotifyStateBackStep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	TotalNotifyDuration = TotalDuration;
	ElapsedTime = 0.f;

	StartLocation = MeshComp->GetOwner()->GetActorLocation();

	FVector BackDir = -MeshComp->GetOwner()->GetActorForwardVector();
	
	float BackkStepDistance = 500.f;

	TargetLocation = StartLocation + BackDir * BackkStepDistance;
}

void UAnimNotifyStateBackStep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!MeshComp || !MeshComp->GetOwner())
		return;

	ElapsedTime += FrameDeltaTime;

	float Alpha = FMath::Clamp(ElapsedTime / TotalNotifyDuration, 0.f, 1.f);

	FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);

	MeshComp->GetOwner()->SetActorLocation(NewLocation);
}

void UAnimNotifyStateBackStep::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp || !MeshComp->GetOwner())
		return;
	
}
