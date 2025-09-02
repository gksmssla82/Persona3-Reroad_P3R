// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraActionBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACameraActionBase::ACameraActionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACameraActionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraActionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraActionBase::InitializeCameraRotation()
{
	SetActorRotation(FRotator(0, 0, 0));
	SpringArmComponent->SetRelativeRotation(CameraArmRotation);
	SpringArmComponent->SetRelativeLocation(CameraArmLocation);
	CameraComponent->SetRelativeRotation(CameraRotation);
	CameraComponent->SetRelativeLocation(CameraLocation);
}

