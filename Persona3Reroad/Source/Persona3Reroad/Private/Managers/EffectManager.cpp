// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/EffectManager.h"

#include "System/BattleInstanceSubsystem.h"

// Sets default values
AEffectManager::AEffectManager()
{
	PrimaryActorTick.bCanEverTick = false;

}


void AEffectManager::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_EffectManager(this);
}

UNiagaraSystem* AEffectManager::Get_Effect(FName Name) const
{
	if (const TObjectPtr<UNiagaraSystem>* Found = EffectMaps.Find(Name))
	{
		return Found->Get();
	}

	UE_LOG(LogTemp, Error, TEXT("%s Effect not found"), *Name.ToString());
	
	return nullptr;
}




