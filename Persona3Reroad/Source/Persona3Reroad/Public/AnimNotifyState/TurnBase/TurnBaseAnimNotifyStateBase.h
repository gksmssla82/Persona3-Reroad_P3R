// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TurnBaseAnimNotifyStateBase.generated.h"

class UTurnComponent;
class ATBC_CharacterBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UTurnBaseAnimNotifyStateBase : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UTurnBaseAnimNotifyStateBase();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	TObjectPtr<ATBC_CharacterBase> TurnCharacter;
	UPROPERTY()
	TObjectPtr<UTurnComponent> TurnComponent;
};
