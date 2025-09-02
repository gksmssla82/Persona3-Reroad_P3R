// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraEnemyAttackEnd.h"

#include "GameFramework/SpringArmComponent.h"

ACameraEnemyAttackEnd::ACameraEnemyAttackEnd()
{
	CameraArmRotation = FRotator(0.0f,-180.0f,0.0f);
	SpringArmComponent->SetRelativeRotation(CameraArmRotation);
	SpringArmComponent->TargetArmLength = 450.0f;
}

void ACameraEnemyAttackEnd::BeginPlay()
{
	Super::BeginPlay();
}
