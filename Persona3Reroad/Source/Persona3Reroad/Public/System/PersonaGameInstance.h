// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PersonaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UPersonaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPersonaGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override; // 게임 시작시
	virtual void Shutdown() override; // 게임 종료시
	
	
};
