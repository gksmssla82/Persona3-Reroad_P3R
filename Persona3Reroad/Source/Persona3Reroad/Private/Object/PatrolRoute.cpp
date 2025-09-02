// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/PatrolRoute.h"

#include "Components/SplineComponent.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));
	PatrolRoute->SetupAttachment(DefaultRoot);
	

}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}



FVector APatrolRoute::GetSplinePointAsWorldPostion()
{
	return PatrolRoute->GetLocationAtSplinePoint(PatrolIndex,ESplineCoordinateSpace::World);
}

void APatrolRoute::IncrementPatrolRoute()
{
	if (!PatrolRoute)
	{
		UE_LOG(LogTemp, Error, TEXT("PatrolRoute::IncrementPatrolRoute"));
		return;
	}

	PatrolIndex += Direction;

	const int32 LastIndex = PatrolRoute->GetNumberOfSplinePoints() - 1;

	if (PatrolIndex == LastIndex)
	{
		Direction = -1;
	}
	else if (PatrolIndex == 0)
	{
		Direction = 1;
	}
	
}

