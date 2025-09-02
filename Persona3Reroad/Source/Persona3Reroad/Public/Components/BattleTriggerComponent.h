// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleTriggerComponent.generated.h"


class ATBC_CharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONA3REROAD_API UBattleTriggerComponent : public UActorComponent
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this component's properties
	UBattleTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerInfo")
	int EnemyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerInfo")
	TArray<TSubclassOf<ATBC_CharacterBase>> EnermyType;
};
