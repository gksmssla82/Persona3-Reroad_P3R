// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/EnemyBattlePositionAxis.h"

#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Components/ArrowComponent.h"
#include "Object/EnemyBattlePostion.h"
#include "System/BattleInstanceSubsystem.h"

// Sets default values
AEnemyBattlePositionAxis::AEnemyBattlePositionAxis()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Cube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>CubeMaterial(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	StaticMeshComponent->SetStaticMesh(Cube.Object);
	StaticMeshComponent->SetMaterial(0,CubeMaterial.Object);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RootComponent = StaticMeshComponent;

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(StaticMeshComponent);
	Arrow->SetRelativeLocation(FVector(0,0,30.0f));
	Arrow->ArrowSize = 1.5f;
	Arrow->ArrowLength = 100.0f;
	Arrow->SetArrowColor(FLinearColor::Red);
	

	
	EnemyBattlePostion = AEnemyBattlePostion::StaticClass();

	this->SetActorHiddenInGame(true);
	this->GetRootComponent()->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AEnemyBattlePositionAxis::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_EnemyBattlePositionAxis(this);
}

void AEnemyBattlePositionAxis::Spawn_BattlePositionAndEnemy(TArray<TSubclassOf<ATBC_EnemyBase>> SpawnEnemy, int8 EnemyCount)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FRotator Rotation = GetActorRotation();
	
	if (EnemyCount == 1)
	{
		AEnemyBattlePostion* BattlePos = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(-200.f,0.f,38.f),Rotation, SpawnParameters);
		BattlePos->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos->SpawnClass = SpawnEnemy[0];
		BattlePos->SpawnActor();
	}
	else if (EnemyCount == 2)
	{
		AEnemyBattlePostion* BattlePos = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(0.f,200.f,38.f),Rotation, SpawnParameters);
		BattlePos->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos->SpawnClass = SpawnEnemy[0];
		BattlePos->SpawnActor();
		AEnemyBattlePostion* BattlePos2 = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(0.f,-200.f,38.f),Rotation, SpawnParameters);
		BattlePos2->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos2->SpawnClass = SpawnEnemy[1];
		BattlePos2->SpawnActor();
	}

	else if (EnemyCount == 3)
	{
		AEnemyBattlePostion* BattlePos = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(200.f,200.f,38.f),Rotation, SpawnParameters);
		BattlePos->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos->SpawnClass = SpawnEnemy[0];
		BattlePos->SpawnActor();
		AEnemyBattlePostion* BattlePos2 = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(-200.f,0.f,38.f),Rotation, SpawnParameters);
		BattlePos2->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos2->SpawnClass = SpawnEnemy[1];
		BattlePos2->SpawnActor();
		AEnemyBattlePostion* BattlePos3 = GetWorld()->SpawnActor<AEnemyBattlePostion>(EnemyBattlePostion,FVector(200.f,-200.f,38.f),Rotation, SpawnParameters);
		BattlePos3->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		BattlePos3->SpawnClass = SpawnEnemy[2];
		BattlePos3->SpawnActor();
	}
}



