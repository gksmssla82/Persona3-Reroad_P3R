// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPS/TPS_CharacterBase.h"
#include "Components/BattleTriggerComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Interface/AIInterface.h"
#include "TPS_Enemy_Trigger01.generated.h"

class ATBC_EnemyBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ATPS_Enemy_Trigger01 : public ATPS_CharacterBase, public IAIInterface
{
	GENERATED_BODY()

public:
	ATPS_Enemy_Trigger01(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	
	

private:
	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void Set_Enemy();
	UFUNCTION()
	void BattleReady();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBattleTriggerComponent> BattleTiggerComponent;

	UPROPERTY(EditAnywhere, Category=Spawn)
	int EnemyCount = 0;
	UPROPERTY(EditAnywhere, Category=Spawn)
	TArray<TSubclassOf<ATBC_EnemyBase>> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Patrol)
	TObjectPtr<APatrolRoute> PatrolRoute;

private:

	FTimerHandle BattleReadyTimerHandle;
	FTimerHandle EnemyDestroyTimerHandle;
	float BattleReadyTime = 0.5f;
	
};
