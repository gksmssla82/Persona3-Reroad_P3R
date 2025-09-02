// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/PlayerBattlePostion.h"

#include "Components/ArrowComponent.h"

APlayerBattlePostion::APlayerBattlePostion()
{
	Arrow->SetArrowColor(FLinearColor::Green);

	
	
}

void APlayerBattlePostion::BeginPlay()
{
	Super::BeginPlay();

	//SpawnActor();
}


