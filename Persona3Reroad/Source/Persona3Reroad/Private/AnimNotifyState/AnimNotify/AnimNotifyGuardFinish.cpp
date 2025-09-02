// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotify/AnimNotifyGuardFinish.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/TurnComponent.h"

UAnimNotifyGuardFinish::UAnimNotifyGuardFinish()
{
}

void UAnimNotifyGuardFinish::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyGuardFinish::Notify"));

	ATBC_CharacterBase* Player = Cast<ATBC_CharacterBase>(MeshComp->GetOwner());
	
	if (Player != nullptr)
	{
		Player->TurnComponent->EndUnitTurn();
	}
	
	
}
