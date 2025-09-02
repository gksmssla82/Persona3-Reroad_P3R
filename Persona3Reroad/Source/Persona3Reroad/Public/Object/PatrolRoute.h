// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class PERSONA3REROAD_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	FVector GetSplinePointAsWorldPostion();

	UFUNCTION(BlueprintCallable)
	void IncrementPatrolRoute();


private:
	UPROPERTY(VisibleDefaultsOnly, Category="Component")
	TObjectPtr<USceneComponent> DefaultRoot;
	UPROPERTY(VisibleDefaultsOnly, Category="Component")
	TObjectPtr<USplineComponent> PatrolRoute;
	UPROPERTY()
	int32 PatrolIndex = 0;
	UPROPERTY()
	int32 Direction = 0;

};
