// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotify/AnimNotifyGunEquip.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"


UAnimNotifyGunEquip::UAnimNotifyGunEquip()
{
}

void UAnimNotifyGunEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                 const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ATBC_PlayerBase* Player = Cast<ATBC_PlayerBase>(MeshComp->GetOwner());

	if (Player != nullptr)
	{
		if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Melee)
		{
			Player->MeleeWeapon->SetVisibility(false);
		}
		else if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Ranged)
		{
			Player->RangedWeapon->SetVisibility(false);
		}
	
		Player->Gun->SetVisibility(true);
	}
}
