// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	Instant,
	forTurns,
	Infinite,
	Temporary
};

UENUM(BlueprintType)
enum class ETargetStat : uint8
{
	MinValue,
	MinValueMod,
	MaxValue,
	MaxValueMod,
	CurrentValue,
	CurrentValueMod,
};

UENUM(BlueprintType)
enum class EEffectMath : uint8
{
	Add,
	Mulitply,
	Divide,
	Override
};

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class EMovementSpeed : uint8
{
	PAUSE UMETA(DisplayName = "PAUSE"),
	WALK UMETA(DisplayName = "WALK"),
	RUN UMETA(DisplayName = "RUN"),
	SPRINT UMETA(DisplayName = "SPRINT")
};

UENUM(BlueprintType)
enum class EAiState : uint8
{
	Passive,
	Attacking,
	Frozen,
	Investigating,
	Dead
};

UENUM(BlueprintType)
enum class ESence: uint8
{
	Sight,
	Hearing,
	Damage
};

UENUM(BlueprintType)
enum class EElement : uint8
{
	None,
	Slash, // 참격
	Blow, // 타격
	Penetration, // 관통
	Fire,
	Ice,
	Electric,
	Wind,
	Light,
	Dark,
	Heal,
	Suport
};

UENUM(Blueprintable)
enum class EWeaponType : uint8
{
	Melee,
	Ranged
};

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	SingleTarget,
	AllTarget,
	AllEnemy,
	AllPlayer
};

UENUM(BlueprintType)
enum class ESkillDamageType : uint8
{
	Small,
	Medium,
	Large
};


