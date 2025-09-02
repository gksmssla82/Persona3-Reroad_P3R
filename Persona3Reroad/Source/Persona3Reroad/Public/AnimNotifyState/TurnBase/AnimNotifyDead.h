// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyDead.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyDead : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotifyDead();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
