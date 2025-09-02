// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/BattlePostion.h"
#include "EnemyBattlePostion.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API AEnemyBattlePostion : public ABattlePostion
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AEnemyBattlePostion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void SpawnActor() override;

private:
	
	TObjectPtr<UNiagaraSystem> EnemySpawnVfx;
	TObjectPtr<UNiagaraComponent> EnemySpawnVfxComponent;

	
};
