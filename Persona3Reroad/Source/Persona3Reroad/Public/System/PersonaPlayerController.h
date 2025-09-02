// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PersonaPlayerController.generated.h"

class UCharacterMovementComponent;
class APlayerCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */


UCLASS()
class PERSONA3REROAD_API APersonaPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APersonaPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	
};
