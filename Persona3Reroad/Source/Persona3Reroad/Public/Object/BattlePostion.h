// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "GameFramework/Actor.h"
#include "BattlePostion.generated.h"

class UArrowComponent;

UCLASS()
class PERSONA3REROAD_API ABattlePostion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattlePostion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SpawnActor();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> SphereMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> Arrow;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnType)
	TSubclassOf<ATBC_CharacterBase> SpawnClass;
	UPROPERTY(BlueprintReadWrite, Category=SpawnType)
	TObjectPtr<ATBC_CharacterBase> SpawnCharacter;
	

};
