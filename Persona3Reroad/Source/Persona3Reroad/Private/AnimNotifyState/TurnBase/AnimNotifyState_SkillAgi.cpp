// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyState_SkillAgi.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Components/TurnComponent.h"
#include "Managers/EffectManager.h"
#include "System/BattleInstanceSubsystem.h"

UAnimNotifyState_SkillAgi::UAnimNotifyState_SkillAgi()
{
}

void UAnimNotifyState_SkillAgi::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !MeshComp->GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("NotifySkillState Faild!"));
		return;
	}

	
	if (ATBC_CharacterBase* Character = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
	{
		UE_LOG(LogTemp, Display, TEXT("Notify Character : %s!"),*Character->GetName());

		if (Character->TurnComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("Notify TurnComponent Get!"));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Notify TurnComponent Null!"));
		}

		
	}

	
}

void UAnimNotifyState_SkillAgi::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
