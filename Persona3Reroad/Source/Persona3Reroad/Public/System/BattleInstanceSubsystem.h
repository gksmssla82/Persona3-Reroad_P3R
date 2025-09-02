// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraEnemyAttackStart.h"
#include "Managers/CameraManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattleInstanceSubsystem.generated.h"

class ABgmManager;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleInstanceWidgetDelegate);

class ASkillManager;
class AEffectManager;
class ATPS_Enemy_Trigger01;
class ABattlePosses;
class ACharacterBase;
class AEnemyBattlePositionAxis;
class ATPS_MainPlayer;
class ABattlePostion;
class ATBC_EnemyBase;
class ATBC_CharacterBase;
class ATBC_PlayerBase;
class ACameraManager;



UCLASS(Blueprintable)
class PERSONA3REROAD_API UBattleInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	void TurnRequest();
	UFUNCTION(BlueprintCallable)
	void StartTurn();
	UFUNCTION(BlueprintCallable)
	void ReadyNextTurn();
	UFUNCTION(BlueprintCallable)
	void EndBattle();

public:
	UFUNCTION(BlueprintCallable)
	void Make_TurnTable();
	UFUNCTION(BlueprintCallable)
	void Make_MonsterData();

public:
	UFUNCTION(BlueprintCallable)
	bool AllEnemyIsSturn();
	bool AllEnemyIsDead();
public:
	void Register_TPSMainPlayer(TObjectPtr<ATPS_MainPlayer> Player);
	void Register_PlayerParty(ATBC_PlayerBase* Player);
	void Register_EnemyParty(ATBC_EnemyBase* Enemy);
	void Register_EnemyBattlePostion(ABattlePostion* Postion);
	void Register_EnemyBattlePositionAxis(AEnemyBattlePositionAxis* Axis);
	void Register_TurnOwner(ATBC_CharacterBase* Owner);
	void Register_BattlePosses(ABattlePosses* Posses);
	void Register_CameraManager(ACameraManager* CameraManager);
	void Register_CurrentTriggerEnemy(ATPS_Enemy_Trigger01* Enemy);
	void Register_EffectManager(AEffectManager* EffectManager);
	void Register_SKillManager(ASkillManager* SkillManager);
	void Register_BgmManager(ABgmManager* BgmManager);

public:
	void Possess_TPSMainPlayer() const;

public:
	void EnemyIsLookAtPlayer(ATBC_CharacterBase* Target) const;
	UFUNCTION(BlueprintCallable)
	void EnemyPartyAllDestroy();


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TArray<ATBC_CharacterBase*> TurnOrder;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TArray<ATBC_PlayerBase*> PlayerParty;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TArray<ATBC_EnemyBase*> EnemyParty;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TArray<ABattlePostion*> EnemyBattlePostions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TObjectPtr<ATPS_MainPlayer> MainPlayer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TObjectPtr<AEnemyBattlePositionAxis> EnemyBattlePositionAxis;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle")
	TObjectPtr<ATBC_CharacterBase> TurnOwner;

	UPROPERTY(BlueprintReadOnly, Category="Turn Battle")
	TObjectPtr<ABattlePosses> BattlePossesPawn;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraEnemyAttackStart> CameraEnemyAttack;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACameraManager> BattleCameraManager;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AEffectManager> BattleEffectManager;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABgmManager> BattleBGMManager;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATPS_Enemy_Trigger01> CurrentTriggerEnemy;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASkillManager> BattleSkillManager;
	
	bool IsTurnInProgress = false;
	bool IsTurnMake = true;

	UPROPERTY()
	FBattleInstanceWidgetDelegate ReadyNextTurnWidgetDelegate;
	
	
};
