// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_MiniMapActor.generated.h"

UCLASS()
class PERSONA3REROAD_API ABase_MiniMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_MiniMapActor();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* TileRoot;

	UPROPERTY(VisibleAnywhere)
	USceneCaptureComponent2D* CaptureComponent;

	// 스태틱 메시들
	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> TileArray;

	// 타일이 이미 보여졌는지 여부
	UPROPERTY()
	TArray<bool> RevealedArray;

	// 플레이어 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> Player;

	// 타일이 보여지는 거리 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectiveRange;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	// 타일 초기화
	void InitializeTiles();

	// 타일 상태 갱신
	void UpdateTileVisibility();
};
