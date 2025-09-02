// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyStateActiveSkill_Agi.generated.h"

class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyStateActiveSkill_Agi : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyStateActiveSkill_Agi();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
};
