// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/EnemyBattlePostion.h"

#include "NiagaraComponent.h"
#include "Components/ArrowComponent.h"
#include "Object/EnemyBattlePositionAxis.h"
#include "NiagaraFunctionLibrary.h"
#include "System/BattleInstanceSubsystem.h"

AEnemyBattlePostion::AEnemyBattlePostion()
{
	Arrow->SetArrowColor(FLinearColor::Red);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SpawnVfx(TEXT("/Script/Niagara.NiagaraSystem'/Game/Hun0FX/StylizedVFX_v02/FX/NS_Mob_Summon.NS_Mob_Summon'"));

	if (SpawnVfx.Succeeded())
	{
		EnemySpawnVfx = SpawnVfx.Object;
	}
}

void AEnemyBattlePostion::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_EnemyBattlePostion(this);
	

	
	
}

void AEnemyBattlePostion::SpawnActor()
{
	Super::SpawnActor();
	SpawnCharacter->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnCharacter->SetActorLocation(this->GetActorLocation());
	EnemySpawnVfxComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EnemySpawnVfx, GetActorLocation());
	EnemySpawnVfxComponent->SetAutoDestroy(true);
}



