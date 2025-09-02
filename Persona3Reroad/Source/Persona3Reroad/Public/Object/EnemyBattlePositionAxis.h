// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBattlePositionAxis.generated.h"

class ATBC_EnemyBase;
class AEnemyBattlePostion;
class UArrowComponent;

UCLASS()
class PERSONA3REROAD_API AEnemyBattlePositionAxis : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBattlePositionAxis();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Spawn_BattlePositionAndEnemy(TArray<TSubclassOf<ATBC_EnemyBase>> SpawnEnemy, int8 EnemyCount);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY()
	TObjectPtr<UArrowComponent> Arrow;
	UPROPERTY()
	TSubclassOf<AEnemyBattlePostion> EnemyBattlePostion;



};
