// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActionBase.h"
#include "CameraEnemyAttackStart.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ACameraEnemyAttackStart : public ACameraActionBase
{
	GENERATED_BODY()
public:
	ACameraEnemyAttackStart();

protected:
	virtual void BeginPlay() override;
};
