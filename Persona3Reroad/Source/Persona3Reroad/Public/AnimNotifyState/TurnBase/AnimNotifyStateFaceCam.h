// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyStateFaceCam.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyStateFaceCam : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UAnimNotifyStateFaceCam();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
};
