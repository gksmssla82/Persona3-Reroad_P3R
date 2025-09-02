// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPS/TPS_CharacterBase.h"
#include "TPS_FriendBase.generated.h"

class AAIController;
class ATPS_MainPlayer;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ATPS_FriendBase : public ATPS_CharacterBase
{
	GENERATED_BODY()

public:
	ATPS_FriendBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;


protected:
	UPROPERTY()
	TObjectPtr<AAIController> AiController = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="FlowTarget")
	TObjectPtr<ATPS_MainPlayer> MainPlayer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="FlowTarget")
	float Distance = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="FlowTarget")
	int32 FollowIndex = 0;
	
};
