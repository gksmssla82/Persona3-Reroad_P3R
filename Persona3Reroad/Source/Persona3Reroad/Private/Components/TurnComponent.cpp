// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TurnComponent.h"

#include "AIController.h"
#include "GameplayTagsManager.h"
#include "Audio/AudioWidgetSubsystem.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Skill/SkillBase.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"
#include "UI/PopupNamePlateWidget.h"

// Sets default values for this component's properties
UTurnComponent::UTurnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurnComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ATBC_CharacterBase>(GetOwner());
	BattleTransform = Owner->GetActorTransform();

	if (AAIController* AIController = Cast<AAIController>(Owner->GetController()))
	{
		if (UPathFollowingComponent* PFC = AIController->GetPathFollowingComponent())
		{
			PFC->OnRequestFinished.AddUObject(this, &UTurnComponent::OnMoveCompletedCallBack);
		}
	}

	
	if (Owner && Owner->GetMesh() && Owner->GetMesh()->GetAnimInstance())
	{
		UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();
		AnimInstance->OnMontageEnded.AddDynamic(this, &UTurnComponent::OnMontageEndedCallBack);
	}
	
	
}

void UTurnComponent::StartUnitTurn()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	UBattleInstanceSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>();

	// Guard Delete
	if (Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Guard")))
	{
		Owner->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("Stance.Guard"));
	}
	

	// Sturn Delete
	if (Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")))
	{
		Owner->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.Sturn"));
		Owner->StatusComponent->SturnVfx_Off();
		EndUnitTurn();
		return;
	}

	if (Subsystem->AllEnemyIsSturn())
	{
		if (Subsystem->AllEnemyIsDead())
		{
			EndUnitTurn();
			return;
		}
		
		GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(FGameplayTag::RequestGameplayTag("Widget.Battle.AllOutAttack"))->AddViewportEvent();
	}

	
	// Owner Is Player
	if (Owner->IsA(ATBC_PlayerBase::StaticClass()))
	{
		if (PC && Owner)
		{
			Subsystem->EnemyIsLookAtPlayer(Owner);
			PC->SetViewTarget(Owner);

			
			if (Subsystem->EnemyParty.Num() > 0)
			{
				UE_LOG(LogTemp, Error, TEXT("Target Charge : %s"),
					   *Subsystem->EnemyParty[0]->GetName());
			}
			
			FGameplayTag GameTag = UGameplayTagsManager::Get().
				RequestGameplayTag(FName("Widget.Battle.ActionCommends"));

			if (UWidgetInstanceSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>())
			{
				UBaseUIWidget* Widget = Sub->FindRegistryWidgetMap(GameTag);
				Sub->PushWidget(Widget);
			}
			if (OnWidgetTurnStarted.IsBound())
			{
				OnWidgetTurnStarted.Broadcast();
			}

			if (Subsystem->AllEnemyIsSturn())
			{
				UE_LOG(LogTemp, Error, TEXT("적군 모두 기절!"));
				GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->ClearWidgetStack();
				GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(FGameplayTag::RequestGameplayTag("Widget.Battle.AllOutAttack"))->AddViewportEvent();
				
			}
			
		}
	}

	// Owner Is Enemy
	if (Owner->IsA(ATBC_EnemyBase::StaticClass()))
	{
		// 플레이어 중 랜덤 인덱스 뽑아서 Targer에 동기화
		if (Subsystem->PlayerParty.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, Subsystem->PlayerParty.Num() - 1);
			Target = Subsystem->PlayerParty[RandomIndex];
		}
		

		PC->SetViewTarget(Owner);

		// 현재 스킬리스트중 랜덤으로 선택스킬 변경 
		int32 RandomSkill = FMath::RandRange(0, Owner->SkillList.Num() - 1);
		Owner->CurrentSkill = Owner->SkillList[RandomSkill];

		Owner->CurrentSkill->Set_Element(Owner);
		
		Subsystem->BattleCameraManager->ToStartFromEndCamera(Owner, "EnemyAttackStart", "EnemyAttackEnd", 3.0f);
		Subsystem->EnemyIsLookAtPlayer(Target);
		//Create Monster Skill NamePlate
		if (GetWorld())
		{
			if (UWidgetInstanceSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>())
			{
				if (UBaseUIWidget* MakeWidget = Sub->FindRegistryWidgetMap(
					FGameplayTag::RequestGameplayTag(FName("Widget.Battle.NamePlate.MonsterSkill"))))
				{
					if (UPopupNamePlateWidget* MakeNamePlate = Cast<UPopupNamePlateWidget>(MakeWidget))
					{
						FName MakeName = Owner->CurrentSkill->GetSkillInfo().SkillName;
						MakeNamePlate->SetNamePlate(FText::FromName(MakeName));
						MakeNamePlate->AddViewportEvent();
					}
				}
			}
		}

		if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
		{
			if (UAnimMontage* SkillMontage = Owner->Montages.FindRef("EnemySkill"))
			{
				UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();

				AnimInstance->Montage_Play(SkillMontage);
			}
		}
	}
}


void UTurnComponent::EndUnitTurn()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->ClearWidgetStack();

	if (OnWidgetTurnEnded.IsBound())
	{
		OnWidgetTurnEnded.Broadcast();
	}


	UE_LOG(LogTemp, Display, TEXT("%s End 유닛턴"),*Owner->GetName());
	
	OnTurnEnded.Broadcast();

	
	// 베틀 턴테이블 다시
	//BeginBattle();
}

void UTurnComponent::AttackCommand() 
{
	GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->ClearWidgetStack();
	
		Owner->StatusComponent->CalculateStance(Owner,Target);
	
		if (Owner->StatusComponent->Get_Status().WeaponType == EWeaponType::Melee)
		{
			MeleeAttack();
		}
		else if (Owner->StatusComponent->Get_Status().WeaponType == EWeaponType::Ranged)
		{
			RangedAttack();
		}
	
	
}

void UTurnComponent::MeleeAttack() 
{
	
	if (Owner->IsA(ATBC_PlayerBase::StaticClass()))
	{
		Owner->CurrentSkill = Owner->SkillList[0];
		Owner->CurrentSkill->Set_Element(Owner);
		Owner->AiController->MoveToLocation(Target->GetActorLocation(),330.f);
		
	}
	
}

void UTurnComponent::RangedAttack()
{
	
	if (UAnimMontage* AttackMontage = Owner->Montages.FindRef("NormalAttack"))
	{
		ATBC_PlayerBase* Player = Cast<ATBC_PlayerBase>(Owner);
		
		UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();
		UAnimInstance* WeaponAnimInstance = Player->RangedWeapon->GetAnimInstance();

		Owner->CurrentSkill = Owner->SkillList[0];
		Owner->CurrentSkill->Set_Element(Owner);
		
		if (UAnimMontage* WeaponAttackMontage = Owner->Montages.FindRef("RangedWeaponNormalAttack"))
		{
			AnimInstance->Montage_Play(AttackMontage);
			WeaponAnimInstance->Montage_Play(WeaponAttackMontage);
		}
		
	}
}

void UTurnComponent::Defence()
{
}



void UTurnComponent::OnMoveCompletedCallBack(FAIRequestID RequestID, const FPathFollowingResult& Result) 
{

	if (Result.IsSuccess())
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->BattleCameraManager->ToStartFromEndCamera(Target, "EnemyHitStart","EnemyHitEnd", 3.0f);
		if (UAnimMontage* AttackMontage = Owner->Montages.FindRef("NormalAttack"))
		{
			UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();
			
			AnimInstance->Montage_Play(AttackMontage);
		}
		
	}
	
}

void UTurnComponent::OnMontageEndedCallBack(UAnimMontage* Montage, bool bInterrupted) 
{
	if (Owner->Montages.FindRef("NormalAttack") == Montage)
	{
		if (bInterrupted)
		{
			UE_LOG(LogTemp, Error, TEXT("Montage Interrupted"));
		}
		else
		{
			Owner->SetActorTransform(BattleTransform);
			if (Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.OneMore")))
			{
				Owner->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.OneMore"));
				if (!GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->EnemyParty.Num() == 0)
				{
					StartUnitTurn();
				}
				else
				{
					EndUnitTurn();
				}
			}
			else
			{
				EndUnitTurn();
			}
		}
		return;
	}

	if (Owner->Montages.FindRef("EnemySkill") == Montage)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Montage Finish"));
	}
}







