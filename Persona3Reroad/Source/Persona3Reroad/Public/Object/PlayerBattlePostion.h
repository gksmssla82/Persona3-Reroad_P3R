// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/BattlePostion.h"
#include "PlayerBattlePostion.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API APlayerBattlePostion : public ABattlePostion
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APlayerBattlePostion();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
};
