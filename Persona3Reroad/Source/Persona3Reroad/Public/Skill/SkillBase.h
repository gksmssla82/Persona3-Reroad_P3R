// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/StatusComponent.h"
#include "Enum/EnumBase.h"
#include "SkillBase.generated.h"

/**
 * 
 */

class UStatusComponent;



USTRUCT()
struct FSkillInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FName SkillName;

	UPROPERTY(EditAnywhere)
	TArray<FName> SkillExplain;
	
	UPROPERTY(EditAnywhere)
	EElement SkillElement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> Effect;

	UPROPERTY(EditAnywhere)
	ETargetType SkillTargetType;

	UPROPERTY(EditAnywhere)
	ESkillDamageType SkillDamageType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SkillSound;

	UPROPERTY(EditAnywhere)
	float SkillCost;

	UPROPERTY(EditAnywhere)
	float WaitDamageTime;
};

UCLASS(Blueprintable, BlueprintType)
class PERSONA3REROAD_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	USkillBase(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION()
	FORCEINLINE bool CanUseSkill(const UStatusComponent* InitiatorStatus, const USkillBase* Skill) const {return InitiatorStatus->Get_Status().CurrentSp >= Skill->GetSkillInfo().SkillCost;}
	
	FORCEINLINE const FSkillInfo& GetSkillInfo() const {return SkillInfo;} 

	UFUNCTION()
	void Set_Element(const ATBC_CharacterBase* Character);
	
protected:
	UPROPERTY(EditAnywhere)
	FSkillInfo SkillInfo;
};
	
	
