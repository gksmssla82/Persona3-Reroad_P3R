// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/TurnBaseAnimNotifyStateBase.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Components/TurnComponent.h"
#include "System/BattleInstanceSubsystem.h"

UTurnBaseAnimNotifyStateBase::UTurnBaseAnimNotifyStateBase()
{
}

void UTurnBaseAnimNotifyStateBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
}

void UTurnBaseAnimNotifyStateBase::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
}


void UTurnBaseAnimNotifyStateBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
