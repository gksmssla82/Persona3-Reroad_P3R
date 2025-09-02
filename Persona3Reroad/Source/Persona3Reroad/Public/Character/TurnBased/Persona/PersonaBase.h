// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PersonaBase.generated.h"

class UCapsuleComponent;
class USkillBase;

UCLASS()
class PERSONA3REROAD_API APersonaBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APersonaBase();

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Name)
	FName PersonaName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
	TArray<TObjectPtr<USkillBase>> SkillList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
	TObjectPtr<USkillBase> CurrentSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Skill)
	bool bIsAttack = false;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

};
