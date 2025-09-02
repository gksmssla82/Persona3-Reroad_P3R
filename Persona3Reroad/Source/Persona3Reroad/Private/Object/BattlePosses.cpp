// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BattlePosses.h"

#include "System/BattleInstanceSubsystem.h"

// Sets default values
ABattlePosses::ABattlePosses()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	
}

// Called when the game starts or when spawned
void ABattlePosses::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_BattlePosses(this);
}



