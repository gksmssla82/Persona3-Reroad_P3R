// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BattleInstanceSubsystem.h"

#include "LevelSequencePlayer.h"
#include "Character/TPS/TPS_MainPlayer.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"
#include "Components/TurnComponent.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Data/PrimaryData/BaseWidgetPrimaryDataAsset.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Enum/EnumBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/BgmManager.h"
#include "Object/BattlePosses.h"
#include "Object/BattlePostion.h"
#include "Object/EnemyBattlePositionAxis.h"
#include "System/WidgetInstanceSubsystem.h"

void UBattleInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UBattleInstanceSubsystem::TurnRequest()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->Possess(BattlePossesPawn);
	
	// 턴테이블 제작 (Sort)
	Make_TurnTable();

	//Widget Create
	if (UBaseUIWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(
		FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle")))
	{
		MakeWidget->AddViewportEvent(1);
	}
	
	//턴 시작
	StartTurn();

	
}



void UBattleInstanceSubsystem::StartTurn()
{
	if (IsTurnInProgress)
	{
		// 0번인덱스빼고 나머지 다 들어옴
		UE_LOG(LogTemp, Warning, TEXT("Turn already started"));
		return;
	}
	
	if (TurnOrder.IsValidIndex(0) && TurnOrder[0])
	{
		IsTurnInProgress = true;
		// Copy
		ATBC_CharacterBase* TurnBaseCharacter = TurnOrder[0];;

		if (UTurnComponent* TurnComponent = TurnBaseCharacter->FindComponentByClass<UTurnComponent>())
		{
			// 바인딩된 모든 함수를 제거, 현재 복사한 애만 실행되게
			TurnComponent->OnTurnEnded.Clear();
			TurnComponent->OnTurnEnded.AddDynamic(this, &UBattleInstanceSubsystem::ReadyNextTurn);
			
			TurnComponent->StartUnitTurn();
		}
	}
}

void UBattleInstanceSubsystem::ReadyNextTurn()
{
	IsTurnInProgress = false;

	if (ReadyNextTurnWidgetDelegate.IsBound())
	{
		ReadyNextTurnWidgetDelegate.Broadcast();
	}

	if (!EnemyParty.IsValidIndex(0))
	{
		FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle");
		GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->RemoveViewportEvent();

		for (auto& Player : PlayerParty)
		{
			Player->StatusComponent->SturnVfx_Off();
		}

		BattleBGMManager->PlayBGM("BattleEnd", 5.0f);
		
		if (TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Makoto")
		{
			BattleCameraManager->Sequence_MainVictory();
		}
		else if (TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Junpei")
		{
			BattleCameraManager->Sequence_JunpaiVictory();
		}
		else if (TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Yukari")
		{
			BattleCameraManager->Sequence_YukariVictory();
		}
		else if (TurnOrder[0]->StatusComponent->Get_Status().CharacterName == "Mitsuru")
		{
			BattleCameraManager->Sequence_MituruVictory();
		}
		
		return;
	}
	
	
	// 현재 턴 유닛 제거
	if (TurnOrder.IsValidIndex(0))
	{
		TurnOrder.RemoveAt(0);
	}
	
	// 다음 턴 스타트
	if (TurnOrder.IsValidIndex(0))
	{
		StartTurn();
		return;
	}

	// 턴오더가 다 비면
	if (!TurnOrder.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Log, TEXT("All Turn Completed"));
		Make_TurnTable();
		StartTurn();
	}
	
}

void UBattleInstanceSubsystem::EndBattle()
{
	//Widget Remove
	if (UBaseUIWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(
		FGameplayTag::RequestGameplayTag("Widget.Battle.PartyPanel.Battle")))
	{
		MakeWidget->RemoveViewportEvent();
	}
		
	

	/////// 임시 포지션 및 적군 파괴 ///////////
	for (auto* Enemy : EnemyParty)
	{
		if (IsValid(Enemy))
		{
			Enemy->Destroy();
			Enemy = nullptr; 
		}
	}
	EnemyParty.Empty();

	
	TurnOrder.Empty();
	
	for (auto* BattlePos : EnemyBattlePostions)
	{
		BattlePos->Destroy();
	}
	EnemyBattlePostions.Empty();

	// 이거안하면 2번쨰 전투떄 몬스터 반대봄
	EnemyBattlePositionAxis->SetActorRotation(FRotator(0.f,0.f,0.f));
	BattleCameraManager->InitializeSetCamerasRotation();


	for (auto& Player : PlayerParty)
	{
		if (Player->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Guard")))
		{
			Player->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("Stance.Guard"));
		}

		if (Player->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")))
		{
			Player->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.Sturn"));
		}
			
	}

	IsTurnInProgress = false;
	
	
	BattleBGMManager->PlayBGM("FieldBGM",0.1);
	/////////////////////////////////////////////////////
	if (BattleCameraManager->VictorySequencePlayer != nullptr)
	{
		BattleCameraManager->VictorySequencePlayer->Stop();
	}

	for (auto& Player : PlayerParty)
	{
		if (Player != nullptr)
		{
			Player->Gun->SetVisibility(false);
	
			if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Melee)
			{
				Player->MeleeWeapon->SetVisibility(true);
			}
			else if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Ranged)
			{
				Player->RangedWeapon->SetVisibility(true);
			}
		}
	}
	Possess_TPSMainPlayer();
}



void UBattleInstanceSubsystem::Make_TurnTable()
{
	for (ATBC_PlayerBase* Player : PlayerParty)
	{
		TurnOrder.AddUnique(Cast<ATBC_CharacterBase>(Player));
	}
	
	for (ATBC_EnemyBase* Enemy : EnemyParty)
	{
		TurnOrder.AddUnique(Cast<ATBC_CharacterBase>(Enemy));
		UE_LOG(LogTemp, Warning, TEXT("Enemy Name : %s"),*Enemy->GetName());
	}
	
	
	TurnOrder.Sort([](const ATBC_CharacterBase& A, const ATBC_CharacterBase& B)
{
	float SpeedA = A.StatusComponent->Get_Speed();
	float SpeedB = B.StatusComponent->Get_Speed();

	return SpeedA > SpeedB; // 속도 높은 순 (내림차순)
});


	for (auto& Turn : TurnOrder)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Turn order complete, Speed = %d"), *Turn->GetName(), Turn->StatusComponent->Get_Speed());
	}
	
}

void UBattleInstanceSubsystem::Make_MonsterData()
{
	
}

bool UBattleInstanceSubsystem::AllEnemyIsSturn()
{
	for (ATBC_EnemyBase* Enemy : EnemyParty)
	{
		if (IsValid(Enemy) && Enemy->StatusComponent->Get_GameTag().IsValid())
		{
			if (!Enemy->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool UBattleInstanceSubsystem::AllEnemyIsDead()
{
	for (ATBC_EnemyBase* Enemy : EnemyParty)
	{
		if (IsValid(Enemy) && Enemy->StatusComponent->Get_GameTag().IsValid())
		{
			if (!Enemy->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
			{
				return false;
			}
		}
		{
			return false;
		}
	}
	return true;
}

void UBattleInstanceSubsystem::Register_TPSMainPlayer(TObjectPtr<ATPS_MainPlayer>Player)
{
	MainPlayer = Player;
}


void UBattleInstanceSubsystem::Register_PlayerParty(ATBC_PlayerBase* Player)
{
	PlayerParty.AddUnique(Player);
}

void UBattleInstanceSubsystem::Register_EnemyParty(ATBC_EnemyBase* Enemy)
{
	EnemyParty.AddUnique(Enemy);
	
}

void UBattleInstanceSubsystem::Register_EnemyBattlePostion(ABattlePostion* Postion)
{
	EnemyBattlePostions.AddUnique(Postion);
}

void UBattleInstanceSubsystem::Register_EnemyBattlePositionAxis(AEnemyBattlePositionAxis* Axis)
{
	EnemyBattlePositionAxis = Axis;
}

void UBattleInstanceSubsystem::Register_TurnOwner(ATBC_CharacterBase* Owner)
{
	TurnOwner = Owner;
}

void UBattleInstanceSubsystem::Register_BattlePosses(ABattlePosses* Posses)
{
	BattlePossesPawn = Posses;
}

void UBattleInstanceSubsystem::Register_CameraManager(ACameraManager* CameraManager)
{
	BattleCameraManager = CameraManager;
}

void UBattleInstanceSubsystem::Register_CurrentTriggerEnemy(ATPS_Enemy_Trigger01* Enemy)
{
	CurrentTriggerEnemy = Enemy;
}

void UBattleInstanceSubsystem::Register_EffectManager(AEffectManager* EffectManager)
{
	BattleEffectManager = EffectManager;
}

void UBattleInstanceSubsystem::Register_SKillManager(ASkillManager* SkillManager)
{
	BattleSkillManager = SkillManager;
}

void UBattleInstanceSubsystem::Register_BgmManager(ABgmManager* BgmManager)
{
	BattleBGMManager = BgmManager;
}


void UBattleInstanceSubsystem::Possess_TPSMainPlayer() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->Possess(MainPlayer);
	}
	
}

void UBattleInstanceSubsystem::EnemyIsLookAtPlayer(ATBC_CharacterBase* Target) const
{
	
	if (!IsValid(EnemyBattlePositionAxis) || !IsValid(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyIsLookAtPlayer: Invalid Axis or Target"));
		return;
	}
	
	
	const FVector AxisLocation   = EnemyBattlePositionAxis->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();
	
	FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(AxisLocation, TargetLocation);
	
	LookRot.Pitch = 0.f;
	LookRot.Roll  = 0.f;
	
	EnemyBattlePositionAxis->SetActorRotation(LookRot.GetNormalized());

	 for (auto* Enemy : EnemyParty)
	 {
	 	const FVector EnemyLocation = Enemy->GetActorLocation();
	 	const FVector TurnOrderLocation = Target->GetActorLocation();

	 	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, TurnOrderLocation);

	 	LookRotation.Pitch = 0.f;
	 	LookRotation.Roll  = 0.f;
	
	 	Enemy->SetActorRotation(LookRotation.GetNormalized());
	 }
	
}

void UBattleInstanceSubsystem::EnemyPartyAllDestroy()
{
	////// 임시 포지션 및 적군 파괴 ///////////
	for (auto* Enemy : EnemyParty)
	{
		if (IsValid(Enemy))
		{
			TurnOrder.Remove(Enemy);
			Enemy->Destroy();
			Enemy = nullptr; 
		}
	}
	EnemyParty.Empty();

}




