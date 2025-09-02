// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotify/AnimNotifyGunUnEquip.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"

UAnimNotifyGunUnEquip::UAnimNotifyGunUnEquip()
{
}

void UAnimNotifyGunUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	ATBC_PlayerBase* Player = Cast<ATBC_PlayerBase>(MeshComp->GetOwner());

	if (Player != nullptr)
	{
		Player->Gun->SetVisibility(false);
	
		if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Melee)
		{
			Player->MeleeWeapon->SetVisibility(true);
		}
		else if (Player->StatusComponent->Get_Status().WeaponType == EWeaponType::Ranged)
		{
			Player->RangedWeapon->SetVisibility(true);
		}
	}
	
	
}
