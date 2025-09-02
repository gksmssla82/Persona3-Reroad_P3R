// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS_CharacterBase.generated.h"

class UWidgetComponent;
class UTurnBaseAbilityComponent;

UCLASS()
class PERSONA3REROAD_API ATPS_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATPS_CharacterBase(const FObjectInitializer& ObjectInitializerb);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	
	
};





