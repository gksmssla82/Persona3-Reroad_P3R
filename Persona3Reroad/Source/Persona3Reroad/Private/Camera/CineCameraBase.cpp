// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CineCameraBase.h"

#include "CineCameraComponent.h"

// Sets default values
ACineCameraBase::ACineCameraBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCineCameraComponent>("CineCameraComponent");
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACineCameraBase::BeginPlay()
{
	Super::BeginPlay();
	
}



