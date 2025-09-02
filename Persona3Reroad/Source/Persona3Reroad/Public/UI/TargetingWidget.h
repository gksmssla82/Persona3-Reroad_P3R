// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseInputWidget.h"
#include "TargetingWidget.generated.h"

class ATBC_CharacterBase;
class UBaseNamePlateWidget;
class ATBC_PlayerBase;
class ATBC_EnemyBase;
class ATargetingCombatWidgetActor;
class UTargetingWidgetDataAsset;
/**
 *
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetingWidgetDelegate);

UCLASS()
class PERSONA3REROAD_API UTargetingWidget : public UBaseInputWidget
{
	GENERATED_BODY()
public:
	UTargetingWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetOwner(AActor* InOrder);

	FORCEINLINE int32 GetBattleArrayIndex() const {return BattleArrayIndex;};

	//set Battle Array
	void SetEnemyParty(TArray<ATBC_EnemyBase*>* InEnemyParty);
	void SetPlayerParty(TArray<ATBC_PlayerBase*>* InPlayerParty);
	void SetTurnOwner(TArray<ATBC_CharacterBase*>* InTurnOrder);

	//Targeting ActionCommends
	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void StartActionTargeting(const FName InName = FName("Basic"));

	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void EndActionTargeting();

	//Targeting SkillCommends
	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void StartSkillTargeting(const FName InName = FName("Skill"));

	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void EndSkillTargeting();

	//ProgressBar Control
	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void ViewTargetProgressBar();

	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void RemoveTargetProgressBar();
	
	UFUNCTION(BlueprintCallable, Category = "TargetingWidget")
	void ClearTargetProgressBar();

	

private:

	//AllCommends
    void Input_LeftStarted();
	void Input_RightStarted();
	void Input_ConfirmStarted();

	//SkillCommends Only
	void Input_CancelStarted();
	
	//NamePlate
	void AddViewportMonsterNamePlate(const int32 Index = 0) const;
	void AddViewportPlayerNamePlate(const int32 Index = 0) const;

private:
	void StartSmoothRotateToTarget(ATBC_EnemyBase* Target);
	void UpdateSpringArmRotation();
	
	//Data Asset
	UPROPERTY()
	TObjectPtr<UTargetingWidgetDataAsset> WidgetDataAsset;

	//Owner Actor
	UPROPERTY()
	TObjectPtr<ATargetingCombatWidgetActor> WidgetOwner;

	//Battle Array Index
	UPROPERTY()
	int32 BattleArrayIndex;

	// Target
	UPROPERTY()
	TObjectPtr<ATBC_EnemyBase> TargetEnemy;

	//Battle Actor Array
	TArray<ATBC_EnemyBase*>* EnemyParty;
	
	TArray<ATBC_PlayerBase*>* PlayerParty;
	
	TArray<ATBC_CharacterBase*>* TurnOrder;

	//NamePlate
	UPROPERTY()
	TObjectPtr<UBaseNamePlateWidget> MonsterNamePlate;
	UPROPERTY()
	TObjectPtr<UBaseNamePlateWidget> PlayerNamePlate;

	//Widget Animation
	UPROPERTY(Transient,BlueprintReadWrite, Category="Turn Battle",meta= (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> Reset;

	UPROPERTY(Transient,BlueprintReadWrite, Category="Turn Battle",meta= (BindWidgetAnim,AllowPrivateAccess = true))
	TObjectPtr<UWidgetAnimation> TargetEnemyAnim;

	//스킬타입에 맞춰서 수정예정
	UPROPERTY()
	FName AttackType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Turn Battle",meta= (AllowPrivateAccess = true))
	TArray<ATBC_EnemyBase*> TestArray;

private:
	UPROPERTY()
	TObjectPtr<ATBC_PlayerBase> CurrentTurnPlayer;
	FTimerHandle SpringArmRotationTimerHandle;
	float InterpDuration = 0.15f;
	float ElapsedTime = 0.f;

	FRotator SpringArmRotator;
	FRotator TargetRotator;

	bool bIsRotating = false;

public:
	UPROPERTY()
	FTargetingWidgetDelegate PartyPanelBattleSPUpdate;
	
};


