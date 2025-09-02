// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectManager.generated.h"

class UNiagaraSystem;

UCLASS()
class PERSONA3REROAD_API AEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE UNiagaraSystem* Get_Effect(FName Name) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Effect, meta = (AllowPrivateAccess = "true"))
	TMap<FName,TObjectPtr<UNiagaraSystem>> EffectMaps;
	

};
