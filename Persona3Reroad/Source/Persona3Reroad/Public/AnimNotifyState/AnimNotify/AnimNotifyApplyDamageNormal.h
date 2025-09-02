// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NiagaraComponent.h"
#include "AnimNotifyApplyDamageNormal.generated.h"

class ATBC_CharacterBase;
/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API UAnimNotifyApplyDamageNormal : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotifyApplyDamageNormal();
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	void SpawnEffectAndApplyDamge(UWorld* World, const TArray<ATBC_CharacterBase*> Targets, UNiagaraSystem* Vfx, int32 Index, ATBC_CharacterBase* SkillOwner, float Interval);

private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
};
