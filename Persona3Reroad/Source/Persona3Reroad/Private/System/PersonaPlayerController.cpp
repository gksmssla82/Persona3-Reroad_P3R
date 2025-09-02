// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PersonaPlayerController.h"
#include "Enum/EnumBase.h"


APersonaPlayerController::APersonaPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void APersonaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
}

void APersonaPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}

void APersonaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
}

FGenericTeamId APersonaPlayerController::GetGenericTeamId() const
{
	return FGenericTeamId(static_cast<uint8>(EObjectType::Player));
}
