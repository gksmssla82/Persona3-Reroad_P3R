// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor/Base_MiniMapActor.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
ABase_MiniMapActor::ABase_MiniMapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	TileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TileRoot"));
	TileRoot->SetupAttachment(SceneRoot);

	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	CaptureComponent->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ABase_MiniMapActor::BeginPlay()
{
	Super::BeginPlay();
	InitializeTiles();
}

// Called every frame
void ABase_MiniMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTileVisibility();

}

void ABase_MiniMapActor::InitializeTiles()
{
	TileArray.Empty();
	RevealedArray.Empty();

	TArray<USceneComponent*> ChildComponents;
	TileRoot->GetChildrenComponents(false, ChildComponents);

	// 정렬: 이름 기준 오름차순 (Battle_01, Battle_02, ...)
	ChildComponents.Sort([](const USceneComponent& A, const USceneComponent& B) {
		return A.GetName() < B.GetName();
	});

	for (USceneComponent* Child : ChildComponents)
	{
		if (UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Child))
		{
			TileArray.Add(Mesh);
			RevealedArray.Add(false);
			Mesh->SetVisibility(false);
		}
	}
}

void ABase_MiniMapActor::UpdateTileVisibility()
{
	for (int32 i = 0; i < TileArray.Num(); ++i)
	{
		if (!TileArray.IsValidIndex(i) || RevealedArray[i])
		{
			continue;
		}

		UStaticMeshComponent* Tile = TileArray[i];
		if (!Tile)
		{
			continue;
		}

		FVector TileCenter = Tile->GetComponentLocation();
		FVector PlayerLoc = Player->GetActorLocation();
		PlayerLoc.Z = TileCenter.Z;

		float Dist = FVector::Dist(PlayerLoc, TileCenter);

		// ✅ 조건: 원 안에 들어오면 켜기
		if (Dist < EffectiveRange)
		{
			Tile->SetVisibility(true);
			RevealedArray[i] = true;

			// 자식 컴포넌트도 Reveal
			TArray<USceneComponent*> ChildComponents;
			Tile->GetChildrenComponents(true, ChildComponents);
			for (USceneComponent* Child : ChildComponents)
			{
				if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Child))
				{
					Prim->SetVisibility(true, true);
				}
			}
		}
	}
}

