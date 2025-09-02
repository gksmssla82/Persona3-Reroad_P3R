// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillManager.generated.h"

class ATBC_CharacterBase;
class USkillBase;

UCLASS()
class PERSONA3REROAD_API ASkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Add_Skill(FName SkillName, ATBC_CharacterBase* SkillTarget = nullptr, APersonaBase* PersonaSkill = nullptr);

private:
	UPROPERTY(EditAnywhere)
	TMap<FName, TSubclassOf<USkillBase>> Skills;
};
