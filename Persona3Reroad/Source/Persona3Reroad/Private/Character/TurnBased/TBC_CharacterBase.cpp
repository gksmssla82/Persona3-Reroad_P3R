// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TurnBased/TBC_CharacterBase.h"

#include "AIController.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StatusComponent.h"
#include "Components/TurnComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/NavMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/BattleInstanceSubsystem.h"
#include "UI/BaseProgressBarWidget.h"

// Sets default values
ATBC_CharacterBase::ATBC_CharacterBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Mesh Pos,Rot Set / PostProcces
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f,-90.0f,0.0f));
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	TurnComponent = CreateDefaultSubobject<UTurnComponent>(TEXT("TurnComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget ProgressBar"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawAtDesiredSize(true);
	
	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bEnablePhysicsInteraction = false;


	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	
}

// Called when the game starts or when spawnedb
void ATBC_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AiController = Cast<AAIController>(GetController());
	if (UBaseProgressBarWidget* MakeProgressBar = Cast<UBaseProgressBarWidget>(WidgetComponent->GetWidget()))
	{
		MakeProgressBar->Init_ProgressBar(this);
	}
	
}

// Called every frame
void ATBC_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATBC_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATBC_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATBC_CharacterBase::SpawnEffectAndApplyDamge(UWorld* World, const TArray<ATBC_CharacterBase*> Targets,
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
		FTimerDelegate::CreateUObject(this, &ATBC_CharacterBase::SpawnEffectAndApplyDamge, World, Targets, Vfx, Index + 1,  SkillOwner, Interval),
		Interval,
		false
		);
}

void ATBC_CharacterBase::MagicAttack()
{
		
			if (TurnComponent->Get_Target())
			{
				
				if (auto* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
				{

					if (CurrentSkill)
					{
						if (UNiagaraSystem* Skill = CurrentSkill->GetSkillInfo().Effect)
						{
							if (this->IsA(ATBC_PlayerBase::StaticClass()))
							{// 플레이어일 경우
								if (CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
								{
									ATBC_CharacterBase* Target = TurnComponent->Get_Target();
									TArray<ATBC_CharacterBase*> TempArray;
									TempArray.Add(Target);

									SpawnEffectAndApplyDamge(GetWorld(), TempArray, Skill, 0, this, 0.3f);
								}

								else if (CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::AllTarget)
								{
									TArray<ATBC_CharacterBase*> EnemyCharacters;

									for (AActor* Actor : Subsystem->EnemyParty)
									{
										if (ATBC_CharacterBase* Enemy = Cast<ATBC_CharacterBase>(Actor))
										{
											EnemyCharacters.Add(Enemy);
										}
									}

									SpawnEffectAndApplyDamge(GetWorld(), EnemyCharacters, Skill, 0, this, 0.3f);
									
								}
							}

							else if (this->IsA(ATBC_EnemyBase::StaticClass()))
							{
								if (this->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
								{
									ATBC_CharacterBase* Target = TurnComponent->Get_Target();
									TArray<ATBC_CharacterBase*> TempArray;
									TempArray.Add(Target);

									SpawnEffectAndApplyDamge(GetWorld(), TempArray, Skill, 0, this, 0.3f);
								}

								else if (this->CurrentSkill->GetSkillInfo().SkillTargetType == ETargetType::AllTarget)
								{
									TArray<ATBC_CharacterBase*> PlayerCharacters;
									
									for (AActor* Actor : Subsystem->PlayerParty)
									{
										if (ATBC_CharacterBase* Enemy = Cast<ATBC_CharacterBase>(Actor))
										{
											PlayerCharacters.Add(Enemy);
										}
									}

									SpawnEffectAndApplyDamge(GetWorld(), PlayerCharacters, Skill, 0, this, 0.3f);
								}
							}
							
						}
					}
				}
			}
			////////////////////////////////////////// Effect End ///////////////////////////////////////////////
		

			
}



		

		


void ATBC_CharacterBase::OnDeath()
{
	if (UBattleInstanceSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
	{
		Subsystem->TurnOrder.Remove(this);
		UE_LOG(LogTemp, Error, TEXT("%s 가 TurnOrder에서 삭제"),*this->GetName())
	}

	Destroy();
}



