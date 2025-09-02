// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"

#include "Camera/CameraComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Enum/EnumBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/BattleInstanceSubsystem.h"

ATBC_EnemyBase::ATBC_EnemyBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void ATBC_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_EnemyParty(this);
	UGameplayStatics::PlaySound2D(GetWorld(),SpawnSound);
	
}

void ATBC_EnemyBase::OnDeath()
{
	if (UBattleInstanceSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
	{
		Subsystem->EnemyParty.Remove(this);
		UE_LOG(LogTemp, Error, TEXT("%s 가 EnemyParty에서 삭제"),*this->GetName())
	}
	
	Super::OnDeath();
}

void ATBC_EnemyBase::Set_Enemy_RotationFromAxis()
{
	
}
