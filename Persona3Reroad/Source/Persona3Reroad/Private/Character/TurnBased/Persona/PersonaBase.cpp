// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TurnBased/Persona/PersonaBase.h"

#include "Components/CapsuleComponent.h"

// Sets default values
APersonaBase::APersonaBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetWorldLocationAndRotation(FVector(0.0f,0.0f,-88.0f), FRotator(0.0f,-90.0f,0.0f));
	SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void APersonaBase::BeginPlay()
{
	Super::BeginPlay();
	
}



