// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyDead.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "Character/TurnBased/TBC_CharacterBase.h"

UAnimNotifyDead::UAnimNotifyDead()
{
}

void UAnimNotifyDead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !MeshComp->GetWorld())
	{
		return;
	}

	if (ATBC_CharacterBase* Character = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
	{
		Character->OnDeath();
	}
}
