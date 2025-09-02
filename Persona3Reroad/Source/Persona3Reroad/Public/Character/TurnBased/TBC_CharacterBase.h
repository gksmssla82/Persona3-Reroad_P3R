// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnumBase.generated.h"
#include "GameplayTagContainer.h"
#include "Skill/SkillBase.h"
#include "TBC_CharacterBase.generated.h"


struct FGameplayTagContainer;
class UWidgetComponent;
class UStatusComponent;
class UTurnComponent;
class AAIController;



UCLASS()
class PERSONA3REROAD_API ATBC_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATBC_CharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	void SpawnEffectAndApplyDamge(UWorld* World, const TArray<ATBC_CharacterBase*> Targets, UNiagaraSystem* Vfx, int32 Index, ATBC_CharacterBase* SkillOwner, float Interval);

	UFUNCTION(BlueprintCallable)
	void MagicAttack();
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnDeath();

	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AiController)
	TObjectPtr<AAIController> AiController;
	
 	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UTurnComponent> TurnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TMap<FName,TObjectPtr<UAnimMontage>> Montages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
	TArray<TObjectPtr<USkillBase>> SkillList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
	TObjectPtr<USkillBase> CurrentSkill;


};
