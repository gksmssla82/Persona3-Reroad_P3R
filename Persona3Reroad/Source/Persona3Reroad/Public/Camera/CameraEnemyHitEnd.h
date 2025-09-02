// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActionBase.h"
#include "CameraEnemyHitEnd.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ACameraEnemyHitEnd : public ACameraActionBase
{
	GENERATED_BODY()

public:
	ACameraEnemyHitEnd();

public:
	virtual void BeginPlay() override;
	
};
