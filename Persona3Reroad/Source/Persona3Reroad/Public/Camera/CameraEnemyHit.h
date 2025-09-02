// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActionBase.h"
#include "CameraEnemyHit.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ACameraEnemyHit : public ACameraActionBase
{
	GENERATED_BODY()

public:
	ACameraEnemyHit();

public:
	virtual void BeginPlay() override;
};
