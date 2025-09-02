// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_SturnVfx.generated.h"

class UNiagaraComponent;
class ATBC_CharacterBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyState_SturnVfx : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_SturnVfx();

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


public:
	void CustomNoitifyBegin(ATBC_CharacterBase* Character);
	void CustomNotifyEnd(ATBC_CharacterBase* Character);

private:
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
};
