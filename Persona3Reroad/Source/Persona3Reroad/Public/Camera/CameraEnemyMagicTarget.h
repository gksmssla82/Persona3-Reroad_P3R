// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CameraEnemyMagicTarget.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UCameraEnemyMagicTarget : public UAnimNotify
{
	GENERATED_BODY()

public:
	UCameraEnemyMagicTarget();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
