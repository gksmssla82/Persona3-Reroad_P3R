// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TurnBased/Player/TBC_PlayerBase.h"

#include "Camera/CameraComponent.h"
#include "Character/TurnBased/Persona/PersonaBase.h"
#include "Components/StatusComponent.h"
#include "Enum/EnumBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "System/BattleInstanceSubsystem.h"

ATBC_PlayerBase::ATBC_PlayerBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponents");
	SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,40.0f), FRotator(-5.0f, -15.0f,0.0f));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetRelativeLocation(FVector(0.0f,175.0f,0.0f));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MeleeWeapon = CreateDefaultSubobject<UStaticMeshComponent>("MeleeWeapons");
	MeleeWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeWeapon->SetupAttachment(GetMesh(), FName("Weapon"));

	RangedWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("RangedWeapons");
	RangedWeapon->SetupAttachment(GetMesh(), FName("Weapon"));

	CutinComponent = CreateDefaultSubobject<USkeletalMeshComponent>("CutinComponent");
	CutinComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CutinComponent->SetupAttachment(GetMesh(), FName("Cutin"));
	CutinComponent->SetRelativeLocation(FVector(0.0f, -120.f, 160.f));
	CutinComponent->SetRelativeScale3D(FVector(1.5f,1.5f,1.5f));
	CutinComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	CutinComponent->SetHiddenInGame(true);

	Gun = CreateDefaultSubobject<UStaticMeshComponent>("GunWeapons");
	Gun->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Gun->SetupAttachment(GetMesh(), FName("Gun"));

	
	
}

void ATBC_PlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_PlayerParty(this);

	if (this->StatusComponent->Get_Status().WeaponType == EWeaponType::Melee)
	{
		RangedWeapon->SetVisibility(false);
	}
	else
	{
		MeleeWeapon->SetVisibility(false);
	}

	Gun->SetVisibility(false);

	if (CurrentPersona != nullptr)
	{
		CurrentPersona->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		CurrentPersona->SetActorRelativeLocation(FVector(0.0f, -150.0f, 90.0f));
		CurrentPersona->SetActorHiddenInGame(true);
	}

	SpringArmRotator = SpringArmComponent->GetRelativeRotation();
}

void ATBC_PlayerBase::OnDeath()
{
	if (UBattleInstanceSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
	{
		Subsystem->PlayerParty.Remove(this);
		UE_LOG(LogTemp, Error, TEXT("%s 가 PlayerParty에서 삭제"),*this->GetName())
	}
	
	Super::OnDeath();
}
