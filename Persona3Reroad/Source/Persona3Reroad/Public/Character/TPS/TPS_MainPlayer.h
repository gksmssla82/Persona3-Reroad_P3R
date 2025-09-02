// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPS/TPS_CharacterBase.h"
#include "TPS_MainPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ATPS_MainPlayer : public ATPS_CharacterBase
{
	GENERATED_BODY()
public:
	ATPS_MainPlayer(const FObjectInitializer& ObjectInitializerb);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_CamMove(const FInputActionValue& InputValue);
	void Input_Sprint(const FInputActionValue& InputValue);
	void Input_SprintCancel(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);

private:
	void Set_SprintSpeed();
	void Set_AssultSprntSpeed();
	
protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> PlayerSpringArm;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<USceneComponent>> FollowPointse;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Sensitivity)
	float CamSensitivity = 0.3;

	UPROPERTY(BlueprintReadWrite, Category = Speed)
	float MoveSpeed = 200.0f;
	UPROPERTY(BlueprintReadWrite, Category = Speed)
	bool IsSprint = false;
	
	UPROPERTY(BlueprintReadWrite, Category = Attack)
	bool IsAttack = false;

private:
	FTimerHandle SprintHandle;
	FTimerHandle AssultSprintHandle;
	
};
