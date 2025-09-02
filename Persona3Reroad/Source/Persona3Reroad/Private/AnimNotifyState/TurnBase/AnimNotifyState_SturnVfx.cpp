// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyState_SturnVfx.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Managers/EffectManager.h"
#include "System/BattleInstanceSubsystem.h"

UAnimNotifyState_SturnVfx::UAnimNotifyState_SturnVfx()
{
}

void UAnimNotifyState_SturnVfx::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UAnimNotifyState_SturnVfx::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UAnimNotifyState_SturnVfx::CustomNoitifyBegin(ATBC_CharacterBase* Character)
{
	
}


void UAnimNotifyState_SturnVfx::CustomNotifyEnd(ATBC_CharacterBase* Character)
{
	NiagaraComponent->Deactivate();
}
