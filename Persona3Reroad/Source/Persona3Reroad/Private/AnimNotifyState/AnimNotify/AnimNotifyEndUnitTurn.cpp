// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotify/AnimNotifyEndUnitTurn.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Components/TurnComponent.h"

UAnimNotifyEndUnitTurn::UAnimNotifyEndUnitTurn()
{
}

void UAnimNotifyEndUnitTurn::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !MeshComp->GetWorld())
	{
		return;
	}

	
	if (ATBC_CharacterBase* Owner = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
	{
		Owner->TurnComponent->EndUnitTurn();
	}
}
