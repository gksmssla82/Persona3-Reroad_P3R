// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActionBase.h"
#include "CameraEnemyAttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ACameraEnemyAttackEnd : public ACameraActionBase
{
	GENERATED_BODY()

public:
	ACameraEnemyAttackEnd();

protected:
	virtual void BeginPlay() override;
	
};
