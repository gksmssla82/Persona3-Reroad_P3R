// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyStateActiveSkill_Agi.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Components/TurnComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Managers/EffectManager.h"
#include "Skill/SkillBase.h"
#include "System/BattleInstanceSubsystem.h"

UAnimNotifyStateActiveSkill_Agi::UAnimNotifyStateActiveSkill_Agi()
{
}

void UAnimNotifyStateActiveSkill_Agi::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                  float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !MeshComp->GetWorld())
	{
		return;
	}

	// 몬스터 일 경우
	if (MeshComp->GetOwner()->IsA(ATBC_EnemyBase::StaticClass()))
	{
		if (ATBC_EnemyBase* Owner = Cast<ATBC_EnemyBase>(MeshComp->GetOwner()))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Skill Notify Owner Get Succese"), *Owner->GetName());

			if (UTurnComponent* Component = Owner->TurnComponent)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Skill Notify Owner Get TurnComponent Succese"), *Owner->GetName());

				if (Component->Get_Target())
				{
					UE_LOG(LogTemp, Warning, TEXT("%s Owner Get TurnComponent Target : %s"), *Owner->GetName(), *Component->Get_Target()->GetName())

					auto* Subsystem = MeshComp->GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>();
					
					if (UNiagaraSystem* Skill = Owner->CurrentSkill->GetSkillInfo().Effect)
					{
						if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
						{
							NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), Skill, Component->Get_Target()->GetActorLocation());
						}
						
						else if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::AllEnemy)
						{
							for (auto& Target : Subsystem->PlayerParty)
							{
								NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(MeshComp->GetWorld(), Skill, Target->GetActorLocation());
							}
						}
					}
				}
			}
		}

		
	}
	
}

void UAnimNotifyStateActiveSkill_Agi::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
