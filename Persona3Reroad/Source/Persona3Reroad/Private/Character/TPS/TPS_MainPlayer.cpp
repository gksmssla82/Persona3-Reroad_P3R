// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPS/TPS_MainPlayer.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Data/InputDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/PersonaAssetManager.h"
#include "System/PersonaGameplayTags.h"



ATPS_MainPlayer::ATPS_MainPlayer(const FObjectInitializer& ObjectInitializerb)
	:Super(ObjectInitializerb)
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Spring Arm
	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	PlayerSpringArm->SetupAttachment(RootComponent);
	PlayerSpringArm->TargetArmLength = 400.0f;
	PlayerSpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	// Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PlayerCamera->SetupAttachment(PlayerSpringArm);

	// Weapon
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetRelativeScale3D(FVector(0.7f,0.7f,0.7f));

	// FollowPoint
	 USceneComponent* FollowPoint1  = CreateDefaultSubobject<USceneComponent>("Point1");
	 FollowPoint1->SetupAttachment(RootComponent);
	 FollowPoint1->SetRelativeLocation(FVector(-150.0f, -100.0f, 0.0f));
	 FollowPointse.Add(FollowPoint1);
	
	 USceneComponent* FollowPoint2 = CreateDefaultSubobject<USceneComponent>("Point2");
	 FollowPoint2->SetupAttachment(RootComponent);
	 FollowPoint2->SetRelativeLocation(FVector(-180.0f, 0.0f, 0.0f));
	 FollowPointse.Add(FollowPoint2);
	
	 USceneComponent* FollowPoint3  = CreateDefaultSubobject<USceneComponent>("Point3");
	 FollowPoint3->SetupAttachment(RootComponent);
	 FollowPoint3->SetRelativeLocation(FVector(-150.0f, 100.0f, 0.0f));
	 FollowPointse.Add(FollowPoint3);

	
	
}

void ATPS_MainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_TPSMainPlayer(this);
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon"));
}

void ATPS_MainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float& CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, MoveSpeed, DeltaTime, 8.0f);
	
}

void ATPS_MainPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATPS_MainPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 1. PlayerController 체크
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// 2. LocalPlayer 체크
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			// 3. InputDataAsset 로드
			if (const UInputDataAsset* InputData = UPersonaAssetManager::GetAssetByName<UInputDataAsset>("InputData"))
			{
				// 4. 서브시스템에 MappingContext 등록
				if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				{
					SubSystem->AddMappingContext(InputData->InputMappingContext, 0);
				}

				// 5. EnhancedInputComponent 캐스팅 및 바인딩
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
				{
					if (const UInputAction* MoveAction = InputData->FindInputActionByTag(PersonaGamePlayTags::Input_Action_Move))
					{
						EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
					}

					if (const UInputAction* CamMoveAction = InputData->FindInputActionByTag(PersonaGamePlayTags::Input_Action_CamMove))
					{
						EnhancedInputComponent->BindAction(CamMoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_CamMove);
					}

					if (const UInputAction* SprintAction = InputData->FindInputActionByTag(PersonaGamePlayTags::Input_Action_Sprint))
					{
						EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Sprint);
						EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::Input_SprintCancel);
					}

					if (const UInputAction* AttackAction = InputData->FindInputActionByTag(PersonaGamePlayTags::Input_Action_Attack))
					{
						EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Attack);
					}
				}
			}
		}
	}
}



void ATPS_MainPlayer::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (!IsAttack)
	{
		if (MovementVector.X != 0)
		{
			FRotator Rotator = GetControlRotation();
			FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
			AddMovementInput(Direction, MovementVector.X);
		}

		if (MovementVector.Y != 0)
		{
			FRotator Rotator = GetControlRotation();
			FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
			AddMovementInput(Direction, MovementVector.Y);
		}
	}
}

void ATPS_MainPlayer::Input_CamMove(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X * CamSensitivity);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(-LookAxisVector.Y * CamSensitivity);
	}
}

void ATPS_MainPlayer::Input_Sprint(const FInputActionValue& InputValue)
{
	if (IsSprint || IsAttack)
		return;

	
	IsSprint = true;
	MoveSpeed = 500.0f;
	
	GetWorldTimerManager().SetTimer(SprintHandle, this, &ATPS_MainPlayer::Set_SprintSpeed, 3.0f, false);
	GetWorldTimerManager().SetTimer(AssultSprintHandle, this, &ATPS_MainPlayer::Set_AssultSprntSpeed, 6.0f, false);
}

void ATPS_MainPlayer::Input_SprintCancel(const FInputActionValue& InputValue)
{
	IsSprint = false;
	MoveSpeed = 200.0f;

	GetWorldTimerManager().ClearTimer(SprintHandle);
	GetWorldTimerManager().ClearTimer(AssultSprintHandle);
}

void ATPS_MainPlayer::Input_Attack(const FInputActionValue& InputValue)
{
	MoveSpeed = 0.0f;
	GetWorldTimerManager().ClearTimer(SprintHandle);
	GetWorldTimerManager().ClearTimer(AssultSprintHandle);
	
}

void ATPS_MainPlayer::Set_SprintSpeed()
{
	if (IsSprint)
	{
		MoveSpeed = 600.0f;
	}
}

void ATPS_MainPlayer::Set_AssultSprntSpeed()
{
	if (IsSprint)
	{
		MoveSpeed = 800.0f;
	}
}
