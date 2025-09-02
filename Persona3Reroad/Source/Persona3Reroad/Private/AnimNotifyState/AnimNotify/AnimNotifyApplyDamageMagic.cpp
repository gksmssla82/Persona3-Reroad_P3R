// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotify/AnimNotifyApplyDamageMagic.h"

#include "NiagaraFunctionLibrary.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/TurnComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/BattleInstanceSubsystem.h"

UAnimNotifyApplyDamageMagic::UAnimNotifyApplyDamageMagic()
{
}

void UAnimNotifyApplyDamageMagic::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!MeshComp || !MeshComp->GetWorld())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT(" Owner Get TurnComponent Target"));
	/////////////////////////////////////////// EFFECT ////////////////////////////////////////////////////////
	if (ATBC_CharacterBase* Owner = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
	{
		if (UTurnComponent* Component = Owner->TurnComponent)
		{
			if (Component->Get_Target())
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Owner Get TurnComponent Target : %s"), *Owner->GetName(), *Component->Get_Target()->GetName())

				if (auto* Subsystem = MeshComp->GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
				{

					if (Owner->CurrentSkill)
					{
						if (UNiagaraSystem* Skill = Owner->CurrentSkill->GetSkillInfo().Effect)
						{
							// 플레이어일 경우
							if (Owner->IsA(ATBC_PlayerBase::StaticClass()))
							{
								if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
								{
									ATBC_CharacterBase* Target = Component->Get_Target();
									TArray<ATBC_CharacterBase*> TempArray;
									TempArray.Add(Target);

									SpawnEffectAndApplyDamge(MeshComp->GetWorld(), TempArray, Skill, 0, Owner, 0.3f);
								}

								else if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::AllTarget)
								{
									TArray<ATBC_CharacterBase*> EnemyCharacters;

									for (AActor* Actor : Subsystem->EnemyParty)
									{
										if (ATBC_CharacterBase* Enemy = Cast<ATBC_CharacterBase>(Actor))
										{
											EnemyCharacters.Add(Enemy);
										}
									}

									SpawnEffectAndApplyDamge(MeshComp->GetWorld(), EnemyCharacters, Skill, 0, Owner, 0.3f);
									
								}
							}

							else if (Owner->IsA(ATBC_EnemyBase::StaticClass()))
							{
								if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
								{
									ATBC_CharacterBase* Target = Component->Get_Target();
									TArray<ATBC_CharacterBase*> TempArray;
									TempArray.Add(Target);

									SpawnEffectAndApplyDamge(MeshComp->GetWorld(), TempArray, Skill, 0, Owner, 0.3f);
								}

								else if (Owner->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::AllTarget)
								{
									TArray<ATBC_CharacterBase*> PlayerCharacters;
									
									for (AActor* Actor : Subsystem->PlayerParty)
									{
										if (ATBC_CharacterBase* Enemy = Cast<ATBC_CharacterBase>(Actor))
										{
											PlayerCharacters.Add(Enemy);
										}
									}

									SpawnEffectAndApplyDamge(MeshComp->GetWorld(), PlayerCharacters, Skill, 0, Owner, 0.3f);
								}
							}
							
						}
					}
				}
			}
			////////////////////////////////////////// Effect End ///////////////////////////////////////////////
		

			
		}



		

		
	}

	

	
	
}

void UAnimNotifyApplyDamageMagic::SpawnEffectAndApplyDamge(UWorld* World, const TArray<ATBC_CharacterBase*> Targets,
	UNiagaraSystem* Vfx, int32 Index, ATBC_CharacterBase* SkillOwner, float Interval)
{
	if (Index >= Targets.Num() || !World || !Vfx || !SkillOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Apply SpawnEffectAndApplyDamage!"));
		return;
	}

	ATBC_CharacterBase* Target = Targets[Index];

	if (!Target->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
	{
		FVector BoneLocation = Target->GetMesh()->GetSocketLocation(TEXT("Root"));
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, Vfx, BoneLocation);

		if (SkillOwner->CurrentSkill->GetSkillInfo().SkillSound)
		{
			UGameplayStatics::PlaySoundAtLocation(World, SkillOwner->CurrentSkill->GetSkillInfo().SkillSound, BoneLocation);
		}
	}
	FTimerHandle DamageTimerhandle;
	World->GetTimerManager().SetTimer(
		DamageTimerhandle,
		FTimerDelegate::CreateLambda([=]()
		{
			if (Target)
			{
				Target->StatusComponent->CalculateStance(SkillOwner, Target);
				float Damage = SkillOwner->StatusComponent->CalculateDamage(SkillOwner,Target);
				if (SkillOwner->CurrentSkill->GetSkillInfo().SkillDamageType == ESkillDamageType::Large)
				{
					Damage *= 1.3;
				}
				else if (SkillOwner->CurrentSkill->GetSkillInfo().SkillDamageType == ESkillDamageType::Small)
				{
					Damage *= 1.5;
				}

				else if (SkillOwner->CurrentSkill->GetSkillInfo().SkillDamageType == ESkillDamageType::Large)
				{
					Damage *= 1.8;
				}
				FMath::RoundToInt(Damage);
				Target->StatusComponent->LastStanceCheck();
				Target->StatusComponent->ApplyDamage(Damage);
				Target->StatusComponent->RemoveTag(Target);
				
			}
		}),
		SkillOwner->CurrentSkill->GetSkillInfo().WaitDamageTime,
		false
		);

	FTimerHandle NextAttack;
	World->GetTimerManager().SetTimer(
		NextAttack,
		FTimerDelegate::CreateUObject(this, &UAnimNotifyApplyDamageMagic::SpawnEffectAndApplyDamge, World, Targets, Vfx, Index + 1,  SkillOwner, Interval),
		Interval,
		false
		);
}


