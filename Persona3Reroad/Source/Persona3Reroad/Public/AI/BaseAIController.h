// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enum/EnumBase.h"
#include "BaseAIController.generated.h"

struct FAIStimulus;
class UAISense;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController(const FObjectInitializer& ObjectInitializer);

public:
	virtual void OnPossess(APawn* InPawn);
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "AIState")
	EAiState Get_CurrentState();
	UFUNCTION(BlueprintCallable, Category = "AIState")
	void Set_StatePassive();
	UFUNCTION(BlueprintCallable, Category = "AIState")
	void Set_StateAttacking();
	UFUNCTION(BlueprintCallable, Category = "AIState")
	void Set_StateInvestigating(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "AIState")
	void Set_StateDead();
	UFUNCTION(BlueprintCallable, Category = "AIState")
	void Set_StateFrozen();
	
protected:
	void HandleSensedSight(AActor* Actor);
	

public:
	UFUNCTION()
	virtual void OnPerceptionUpdated_Actors(const TArray<AActor*>& UpdateActors);
	
	virtual bool CanSenseActor(AActor* Actor, TSubclassOf<UAISense> SenseClass, FAIStimulus& OutStimulus);
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISense")
	TObjectPtr<UAIPerceptionComponent> AiPerception;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISense")
	TObjectPtr<UAISenseConfig_Sight> AiSenseConfig_Sight;

protected:
	void StartPassiveTimer();
	void CancelPassiveTimer();
	void SetStateTimer();

private:
	UPROPERTY(BlueprintReadWrite, Category = "BlackBoadKey", meta = (AllowPrivateAccess = "true"))
	FName StateKeyName;
	UPROPERTY(BlueprintReadWrite, Category = "BlackBoadKey", meta = (AllowPrivateAccess = "true"))
	FName TargetActorKeyName;
	UPROPERTY(BlueprintReadWrite, Category = "BlackBoadKey", meta = (AllowPrivateAccess = "true"))
	FName RoutePointKeyName;
	UPROPERTY(BlueprintReadWrite, Category = "BlackBoadKey", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> TargetActor;

protected:
	FTimerHandle PassiveStateTimerHandle;
	float PassiveStateTimer = 5.0f;
	
	
	
};
