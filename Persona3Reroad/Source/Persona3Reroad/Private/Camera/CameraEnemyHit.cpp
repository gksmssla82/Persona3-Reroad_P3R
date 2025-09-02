// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraEnemyHit.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACameraEnemyHit::ACameraEnemyHit()
{
	CameraArmRotation = FRotator(0.0f,160.0f,0.0f);
	SpringArmComponent->SetRelativeRotation(CameraArmRotation);
	SpringArmComponent->TargetArmLength = 500.0f;
}

void ACameraEnemyHit::BeginPlay()
{
	Super::BeginPlay();
}
