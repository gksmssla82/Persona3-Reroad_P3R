// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraEnemyAttackStart.h"

#include "GameFramework/SpringArmComponent.h"
#include "System/BattleInstanceSubsystem.h"

ACameraEnemyAttackStart::ACameraEnemyAttackStart()
{
	CameraArmLocation = FVector(0.0f,0.0f,10.0f);
	CameraArmRotation = FRotator(-30.0f,-170.0f,0.0f);
	SpringArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotation);
	SpringArmComponent->TargetArmLength = 400.0f;
}

void ACameraEnemyAttackStart::BeginPlay()
{
	Super::BeginPlay();
}
