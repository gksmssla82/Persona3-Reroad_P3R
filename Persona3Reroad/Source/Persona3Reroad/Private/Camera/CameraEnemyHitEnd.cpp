// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraEnemyHitEnd.h"

#include "GameFramework/SpringArmComponent.h"

ACameraEnemyHitEnd::ACameraEnemyHitEnd()
{
	CameraArmRotation = FRotator(0.0f,140.0f,0.0f);
	SpringArmComponent->SetRelativeRotation(CameraArmRotation);
	SpringArmComponent->TargetArmLength = 550.0f;
}

void ACameraEnemyHitEnd::BeginPlay()
{
	Super::BeginPlay();
}
