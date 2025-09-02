// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TurnComponent.generated.h"

// Forward declaration only

// forward 선언 유지
struct FAIRequestID;
struct FPathFollowingResult;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEndedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnComponentWidgetDelegate);

class ATBC_CharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PERSONA3REROAD_API UTurnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTurnComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartUnitTurn();

	UFUNCTION(BlueprintCallable)
	void EndUnitTurn();

	FORCEINLINE void Set_Target(ATBC_CharacterBase* TargettingCharacter) { Target = TargettingCharacter; }
	FORCEINLINE ATBC_CharacterBase* Get_Target() {return Target; }

	void AttackCommand();
	void MeleeAttack();
	void RangedAttack();
	void Defence();
	
private:
	void OnMoveCompletedCallBack(FAIRequestID RequestID, const FPathFollowingResult& Result);
	UFUNCTION()
	void OnMontageEndedCallBack(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<ATBC_CharacterBase> Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<ATBC_CharacterBase> Target;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	FTransform BattleTransform;

	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0;

	UPROPERTY(BlueprintAssignable, Category="TurnDelegate")
	FTurnStartedDelegate OnTurnStarted;
	
	UPROPERTY(BlueprintAssignable, Category="TurnDelegate")
	FTurnEndedDelegate OnTurnEnded;

	//Widget Delegate
	UPROPERTY(BlueprintAssignable, Category="TurnDelegate")
	FTurnComponentWidgetDelegate OnWidgetTurnStarted;
	
	UPROPERTY(BlueprintAssignable, Category="TurnDelegate")
	FTurnComponentWidgetDelegate OnWidgetTurnEnded;
	
};