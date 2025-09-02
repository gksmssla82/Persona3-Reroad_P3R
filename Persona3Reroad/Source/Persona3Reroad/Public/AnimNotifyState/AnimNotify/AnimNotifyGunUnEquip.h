// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyGunUnEquip.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyGunUnEquip : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotifyGunUnEquip();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
