// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "TBC_PlayerBase.generated.h"

class APersonaBase;
class UCameraComponent;
class USpringArmComponent;
class AAIController;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ATBC_PlayerBase : public ATBC_CharacterBase
{
	GENERATED_BODY()

public:
	ATBC_PlayerBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void OnDeath() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UStaticMeshComponent> MeleeWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USkeletalMeshComponent> RangedWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<UStaticMeshComponent> Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	TObjectPtr<USkeletalMeshComponent> CutinComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Persona)
	TObjectPtr<APersonaBase> CurrentPersona;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsBattleStart = false;

	UPROPERTY()
	FRotator SpringArmRotator;
};
