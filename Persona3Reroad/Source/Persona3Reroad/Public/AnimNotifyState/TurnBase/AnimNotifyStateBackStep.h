// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState/TurnBase/TurnBaseAnimNotifyStateBase.h"
#include "AnimNotifyStateBackStep.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyStateBackStep : public UTurnBaseAnimNotifyStateBase
{
	GENERATED_BODY()

public:
	UAnimNotifyStateBackStep();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	FVector StartLocation;
	FVector TargetLocation;
	float TotalNotifyDuration = 0.f;
	float ElapsedTime = 0.f;
	

	
};
