// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enum/EnumBase.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

class UNiagaraComponent;
class UAnimNotifyState_SturnVfx;
class ATBC_CharacterBase;

USTRUCT(BlueprintType)
struct FStatus
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName CharacterName;
	UPROPERTY(EditAnywhere)
	float MaxHp = 10;
	UPROPERTY(EditAnywhere)
	float CurrentHp = 10;
	UPROPERTY(EditAnywhere)
	float MaxSp = 10;
	UPROPERTY(EditAnywhere)
	float CurrentSp = 10;
	UPROPERTY(EditAnywhere)
	float Power = 5;
	UPROPERTY(EditAnywhere)
	float Mana = 5;
	UPROPERTY(EditAnywhere)
	float Defence = 5;
	UPROPERTY(EditAnywhere)
	float Speed = 5;
	UPROPERTY(EditAnywhere)
	float Luck = 5;
	UPROPERTY(EditAnywhere)
	float MinDamage = 1;
	UPROPERTY(EditAnywhere)
	float MaxDamage = 5;
	UPROPERTY(EditAnywhere)
	float CriticalProbability = 20;
	UPROPERTY(EditAnywhere)
	float CriticalDamage = 1.5;
	UPROPERTY(EditAnywhere)
	float EvasionProbability = 20;
	UPROPERTY(EditAnywhere)
	float CurrentSturnValue = 0;
	UPROPERTY(EditAnywhere)
	float MaxSturnValue = 100;
	UPROPERTY(EditAnywhere)
	EElement ElementWeak;
	UPROPERTY(EditAnywhere)
	EElement ElementAttack;
	UPROPERTY(EditAnywhere)
	EElement ElementResist;
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitWidgetDelegate,int32,Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSONA3REROAD_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	
protected:
	virtual void BeginPlay() override;
	
public:  
	////// New Logic CalculateStance Once, CalculateDamage_BeforeStance DamageTime, LastStanceCheck() LastDamageTime /////
	void CalculateStance(ATBC_CharacterBase* Attacker, ATBC_CharacterBase* Target);
	float CalculateDamage(ATBC_CharacterBase* Attacker, ATBC_CharacterBase* Target);
	void LastStanceCheck();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void TakeDamage(float Damage);
	void ApplyDamage(float Damage);
	void RemoveTag(ATBC_CharacterBase* Target);
	void DecreaseSp(float Sp);

public:
	FORCEINLINE int Get_Speed() const {return Status.Speed;}
	FORCEINLINE FStatus Get_Status() const {return Status;}
	FORCEINLINE bool Get_IsSturn() const {return bIsSturn;}
	FORCEINLINE FGameplayTagContainer& Get_GameTag()  {return GameTag;}

	// Setter
	FORCEINLINE void Set_ElementAttck(EElement ElemntAttackType)  {Status.ElementAttack = ElemntAttackType;}
	FORCEINLINE void Set_IsSturn(bool IsSturn) {bIsSturn = IsSturn;}
public:
	void SturnVfx_On();
	void SturnVfx_Off();
	

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ATBC_CharacterBase> Owner;
	UPROPERTY(EditAnywhere, Category= Status, meta=(AllowPrivateAccess = "true"))
	FStatus Status;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> SturnNiagaraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer GameTag;

	UPROPERTY(EditDefaultsOnly)
	bool bIsSturn = false;

public:
	UPROPERTY(EditDefaultsOnly)
	bool bIsEvasionOnce = false;

	UPROPERTY(EditDefaultsOnly)
	bool bIsResist = false;

public:
	//no param
	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FStatusDelegate OnMissDeleGate;

	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FStatusDelegate OnResistDeleGate;

	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FStatusDelegate OnWeakDeleGate;

	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FStatusDelegate OnCriticalDeleGate;

	//no param
	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FStatusDelegate OnHitDeleGateNoParam;

	//3 param
	UPROPERTY(BlueprintAssignable, Category="StatusDelegate")
	FOnHitWidgetDelegate OnHitDeleGateThreeParam;

	

	
	
};
