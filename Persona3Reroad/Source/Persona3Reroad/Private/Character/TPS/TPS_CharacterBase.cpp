// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPS/TPS_CharacterBase.h"

#include "Components/WidgetComponent.h"


// Sets default values
ATPS_CharacterBase::ATPS_CharacterBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Mesh Pos,Rot Set / PostProcces
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f,-90.0f,0.0f));
	GetMesh()->SetRenderCustomDepth(true);

	
	
}

// Called when the game starts or when spawned
void ATPS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void ATPS_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPS_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}





