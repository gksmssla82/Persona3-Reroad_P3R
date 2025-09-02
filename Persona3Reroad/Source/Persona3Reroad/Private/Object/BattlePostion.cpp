// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BattlePostion.h"

#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/ArrowComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Object/EnemyBattlePositionAxis.h"
#include "System/BattleInstanceSubsystem.h"

// Sets default values
ABattlePostion::ABattlePostion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("BattlePostion");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Sphere(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	SphereMesh->SetStaticMesh(Sphere.Object);
	SphereMesh->SetMaterial(0,SphereMaterial.Object);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RootComponent = SphereMesh;
	
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(SphereMesh);
	Arrow->SetRelativeLocation(FVector(0,0,30.0f));
	Arrow->ArrowSize = 1.5f;
	Arrow->ArrowLength = 100.0f;
	

	this->SetActorHiddenInGame(true);
	this->GetRootComponent()->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ABattlePostion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABattlePostion::SpawnActor()
{
	if (IsValid(SpawnClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();
		SpawnCharacter = GetWorld()->SpawnActor<ATBC_CharacterBase>(SpawnClass,Location,Rotation, SpawnParameters);
	}
}



