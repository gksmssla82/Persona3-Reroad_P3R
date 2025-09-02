// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetingWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagsManager.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/StatusComponent.h"
#include "Components/TurnComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "Data/UIData/TargetingWidgetDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"
#include "UI/BaseNamePlateWidget.h"
#include "UI/BaseProgressBarWidget.h"
#include "UI/MonsterProgressBarWidget.h"
#include "UI/PopupNamePlateWidget.h"
#include "UI/PopupSkillNamePlateWidget.h"
#include "UI/Combet/TargetingCombatWidgetActor.h"

UTargetingWidget::UTargetingWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTargetingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Cast WidgetDataAsset
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UTargetingWidgetDataAsset>(BaseDataAsset);
	}

	//EnhancedInput Bind
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			//Left
			if (UInputAction* InputActionLeft = WidgetDataAsset->FindInputAction("Left"))
			{
				EnhancedInputComponent->BindAction(InputActionLeft, ETriggerEvent::Started, this,
				                                   &UTargetingWidget::Input_LeftStarted);
			}
			//Right
			if (UInputAction* InputActionRight = WidgetDataAsset->FindInputAction("Right"))
			{
				EnhancedInputComponent->BindAction(InputActionRight, ETriggerEvent::Started, this,
				                                   &UTargetingWidget::Input_RightStarted);
			}
			//Confirm
			if (UInputAction* InputActionConfirm = WidgetDataAsset->FindInputAction("Confirm"))
			{
				EnhancedInputComponent->BindAction(InputActionConfirm, ETriggerEvent::Started, this,
				                                   &UTargetingWidget::Input_ConfirmStarted);
			}

			//*****************Cancel IMC(Sub IMC)****************//
			// Cancel
			if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputActionCancel("Cancel"))
			{
				EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				                                   &UTargetingWidget::Input_CancelStarted);
			}
		}
	}
	//Set TurnBattle Array
	SetPlayerParty(&GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->PlayerParty);
	SetEnemyParty(&GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->EnemyParty);
	SetTurnOwner(&GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder);
	

	//Set NamePlate
	FGameplayTag MonsterNamePlateTag = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Widget.Battle.NamePlate.Monster"));
	if (UBaseUIWidget* MakeMonsterNamePlate = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->
	                                                             FindRegistryWidgetMap(MonsterNamePlateTag))
	{
		MonsterNamePlate = Cast<UBaseNamePlateWidget>(MakeMonsterNamePlate);
	}
	FGameplayTag PlayerNamePlateTag = UGameplayTagsManager::Get().RequestGameplayTag(
		FName("Widget.Battle.NamePlate.Monster"));
	if (UBaseUIWidget* MakePlayerNamePlate = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->
	                                                            FindRegistryWidgetMap(PlayerNamePlateTag))
	{
		PlayerNamePlate = Cast<UBaseNamePlateWidget>(MakePlayerNamePlate);
	}
}

void UTargetingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Reset)
	{
		PlayAnimation(Reset);
	}
}

void UTargetingWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
}

void UTargetingWidget::SetOwner(AActor* InOwner)
{
	WidgetOwner = Cast<ATargetingCombatWidgetActor>(InOwner);
}

void UTargetingWidget::SetEnemyParty(TArray<ATBC_EnemyBase*>* InEnemyParty)
{
	EnemyParty = InEnemyParty;
}

void UTargetingWidget::SetPlayerParty(TArray<ATBC_PlayerBase*>* InPlayerParty)
{
	PlayerParty = InPlayerParty;
}

void UTargetingWidget::SetTurnOwner(TArray<ATBC_CharacterBase*>* InTurnOrder)
{
	if (InTurnOrder)
	{
		TurnOrder = InTurnOrder;
	}
}



void UTargetingWidget::StartActionTargeting(const FName InName)
{
	
	AttackType = InName;
	BattleArrayIndex = 0;

	ClearTargetProgressBar();
	AddViewportMonsterNamePlate(BattleArrayIndex);
	ViewTargetProgressBar();
	AddWidgetMappingContext();
	
	
	if (TargetEnemyAnim)
	{
		//PlayAnimation(TargetEnemyAnim);
	}
	if (WidgetOwner && EnemyParty->Num() > 0)
	{
		
		WidgetOwner->GetWidgetComponent()->SetWorldLocation((*EnemyParty)[0]->GetActorLocation());
	}

	TargetEnemy = (*EnemyParty)[BattleArrayIndex];
	StartSmoothRotateToTarget(TargetEnemy);

	
	
}

void UTargetingWidget::EndActionTargeting()
{
	RemoveWidgetMappingContext();
	ClearTargetProgressBar();
	if (Reset)
	{
		PlayAnimation(Reset);
	}
	MonsterNamePlate->RemoveViewportEvent();
}

void UTargetingWidget::StartSkillTargeting(const FName InName)
{
	
	StartActionTargeting(InName);
	//StartSmoothRotateToTarget(TargetEnemy);
	//Cancel
	if (WidgetDataAsset)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				if (UInputMappingContext* IMC = WidgetDataAsset->GetInputMappingContextCancel())
				{
					{
						Subsystem->AddMappingContext(IMC, 0);
					}
				}
			}
		}
	}
}

void UTargetingWidget::EndSkillTargeting()
{
	EndActionTargeting();
	//Cancel
	if (WidgetDataAsset)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				if (UInputMappingContext* IMC = WidgetDataAsset->GetInputMappingContextCancel())
				{
					{
						Subsystem->RemoveMappingContext(IMC);
					}
				}
			}
		}
	}
	if (UBaseUIWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetStackLastWidget())
	{
		MakeWidget->AddViewportEvent();
	}
}

void UTargetingWidget::ViewTargetProgressBar()
{
	if ((*TurnOrder)[0]->CurrentSkill)
	{
		const FSkillInfo* MakeSkillInfo = &(*TurnOrder)[0]->CurrentSkill->GetSkillInfo();
		if (MakeSkillInfo->SkillTargetType == ETargetType::AllTarget)
		{
			for (int32 i = 0; i < EnemyParty->Num(); i++)
			{
				if (UUserWidget* MakeUserWidget = (*EnemyParty)[i]->WidgetComponent->GetWidget())
				{
					if (UBaseProgressBarWidget* MakeProgressBarWidget = Cast<UBaseProgressBarWidget>(MakeUserWidget))
					{
						MakeProgressBarWidget->PlayProgressAnimation(EProgressBarAnimType::Create);
						UE_LOG(LogTemp, Warning, TEXT("%s"), *MakeProgressBarWidget->GetName());
					}
					if (UMonsterProgressBarWidget* MakeMonsterProgressBar = Cast<UMonsterProgressBarWidget>(MakeUserWidget))
					{
						if (TurnOrder)
						{
							EElement MakeElement = (*TurnOrder)[0]->StatusComponent->Get_Status().ElementAttack;
							MakeMonsterProgressBar->SetElementType(MakeElement);
						}
					}
				}
			}
		}
		else
		{
			if (UUserWidget* MakeUserWidget = (*EnemyParty)[BattleArrayIndex]->WidgetComponent->GetWidget())
			{
				if (UBaseProgressBarWidget* MakeProgressBarWidget = Cast<UBaseProgressBarWidget>(MakeUserWidget))
				{
					MakeProgressBarWidget->PlayProgressAnimation(EProgressBarAnimType::Create);
					UE_LOG(LogTemp, Warning, TEXT("%s"), *MakeProgressBarWidget->GetName());
				}
				if (UMonsterProgressBarWidget* MakeMonsterProgressBar = Cast<UMonsterProgressBarWidget>(MakeUserWidget))
				{
					if (TurnOrder)
					{
						EElement MakeElement = (*TurnOrder)[0]->StatusComponent->Get_Status().ElementAttack;
						MakeMonsterProgressBar->SetElementType(MakeElement);
					}
				}
			}
		}
	}
	else
	{
		if (UUserWidget* MakeUserWidget = (*EnemyParty)[BattleArrayIndex]->WidgetComponent->GetWidget())
		{
			if (UBaseProgressBarWidget* MakeProgressBarWidget = Cast<UBaseProgressBarWidget>(MakeUserWidget))
			{
				MakeProgressBarWidget->PlayProgressAnimation(EProgressBarAnimType::Create);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *MakeProgressBarWidget->GetName());
			}
			if (UMonsterProgressBarWidget* MakeMonsterProgressBar = Cast<UMonsterProgressBarWidget>(MakeUserWidget))
			{
				if (TurnOrder)
				{
					EElement MakeElement = (*TurnOrder)[0]->StatusComponent->Get_Status().ElementAttack;
					MakeMonsterProgressBar->SetElementType(MakeElement);
				}
			}
		}
	}
}

void UTargetingWidget::RemoveTargetProgressBar()
{
	if (UUserWidget* MakeUserWidget = (*EnemyParty)[BattleArrayIndex]->WidgetComponent->GetWidget())
	{
		UBaseProgressBarWidget* MakeProgressBarWidget = Cast<UBaseProgressBarWidget>(MakeUserWidget);
		MakeProgressBarWidget->PlayProgressAnimation(EProgressBarAnimType::Reset);
	}
}

void UTargetingWidget::ClearTargetProgressBar()
{
	for (int i = 0; i < EnemyParty->Num(); i++)
	{
		if (UUserWidget* MakeUserWidget = (*EnemyParty)[i]->WidgetComponent->GetWidget())
		{
			UBaseProgressBarWidget* MakeProgressBarWidget = Cast<UBaseProgressBarWidget>(MakeUserWidget);
			MakeProgressBarWidget->PlayProgressAnimation(EProgressBarAnimType::Reset);
		}
	}
}

void UTargetingWidget::AddViewportMonsterNamePlate(const int32 Index) const
{
	FName EnemyName = (*EnemyParty)[Index]->StatusComponent->Get_Status().CharacterName;
	MonsterNamePlate->SetNamePlate(FText::FromName(EnemyName));
	MonsterNamePlate->AddViewportEvent();
}

void UTargetingWidget::AddViewportPlayerNamePlate(const int32 Index) const
{
	FName EnemyName = (*PlayerParty)[Index]->StatusComponent->Get_Status().CharacterName;
	PlayerNamePlate->SetNamePlate(FText::FromName(EnemyName));
	PlayerNamePlate->AddViewportEvent();
}

void UTargetingWidget::StartSmoothRotateToTarget(ATBC_EnemyBase* Target)
{
	if (!Target && !(*TurnOrder)[0])
	{
		return;
	}

	if (bIsRotating)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpringArmRotationTimerHandle);
	}

	if ((*TurnOrder)[0]->IsA(ATBC_PlayerBase::StaticClass()))
	{
		CurrentTurnPlayer = Cast<ATBC_PlayerBase>((*TurnOrder)[0]);
		bIsRotating = true;
		ElapsedTime = 0.f;
		SpringArmRotator = CurrentTurnPlayer->SpringArmComponent->GetComponentRotation();

		FVector SpringArmLocation = CurrentTurnPlayer->SpringArmComponent->GetComponentLocation();
		FVector TargetLocation = Target->GetActorLocation();
		TargetLocation.Z = SpringArmLocation.Z;

		FVector Direction = (TargetLocation - SpringArmLocation).GetSafeNormal();
		TargetRotator = Direction.Rotation();
		
		GetWorld()->GetTimerManager().SetTimer(SpringArmRotationTimerHandle, this, &ThisClass::UpdateSpringArmRotation, 0.01f, true);
	}
	

	
}

void UTargetingWidget::UpdateSpringArmRotation()
{
	ElapsedTime += 0.01f;
	float Alpha = ElapsedTime / InterpDuration;
	Alpha = FMath::Clamp(Alpha, 0.f, 1.f);
	
	float DeltaYaw = FMath::FindDeltaAngleDegrees(SpringArmRotator.Yaw, TargetRotator.Yaw);
	float InterpolatedYaw = SpringArmRotator.Yaw + DeltaYaw * Alpha;

	FRotator NewRotator = SpringArmRotator;
	NewRotator.Yaw = InterpolatedYaw;

	CurrentTurnPlayer->SpringArmComponent->SetWorldRotation(NewRotator);

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpringArmRotationTimerHandle);
		bIsRotating = false;
	}
}


void UTargetingWidget::Input_LeftStarted()
{

	if ((*TurnOrder)[0]->CurrentSkill)
	{
		FSkillInfo MakeSkillInfo = (*TurnOrder)[0]->CurrentSkill->GetSkillInfo();
		if (MakeSkillInfo.SkillTargetType == ETargetType::AllTarget)
		{
			return;
		}
	}
	
	if (EnemyParty->Num() > 0 && BattleArrayIndex > 0)
	{
		if (WidgetOwner)
		{
			RemoveTargetProgressBar();
			
			BattleArrayIndex--;

			//Monster NamePlate
			AddViewportMonsterNamePlate(BattleArrayIndex);
			ViewTargetProgressBar();
			
			WidgetOwner->GetWidgetComponent()->SetWorldLocation((*EnemyParty)[BattleArrayIndex]->GetActorLocation());
			
		
			
			// FVector MakeVector3D = (WidgetOwner->GetActorLocation() +
			// 		WidgetOwner->GetWidgetComponent()->GetRelativeLocation()) -
			// 	EnemyParty[BattleArrayIndex]->GetActorLocation();
			//
			// UKismetSystemLibrary::MoveComponentTo(WidgetOwner->GetWidgetComponent(),
			//                                       FVector(100.f, 0.0f, 0.0f),
			//                                       FRotator(0, 0, 0),
			//                                       false,
			//                                       false,
			//                                       2.0f,
			//                                       false,
			//                                       EMoveComponentAction::Move,
			//                                       FLatentActionInfo()
			// );
			UE_LOG(LogTemp, Warning, TEXT("%d"), BattleArrayIndex);
			TargetEnemy = (*EnemyParty)[BattleArrayIndex];
			StartSmoothRotateToTarget(TargetEnemy);
		}
	}
}


void UTargetingWidget::Input_RightStarted()
{
	if ((*TurnOrder)[0]->CurrentSkill)
	{
		FSkillInfo MakeSkillInfo = (*TurnOrder)[0]->CurrentSkill->GetSkillInfo();
		if (MakeSkillInfo.SkillTargetType == ETargetType::AllTarget)
		{
			return;
		}
	}
	if (EnemyParty->Num() > 0 && BattleArrayIndex < EnemyParty->Num() - 1)
	{
		if (WidgetOwner)
		{
			RemoveTargetProgressBar();
			BattleArrayIndex++;
			
			//Monster NamePlate
			AddViewportMonsterNamePlate(BattleArrayIndex);
			ViewTargetProgressBar();
			
			
			WidgetOwner->GetWidgetComponent()->SetWorldLocation((*EnemyParty)[BattleArrayIndex]->GetActorLocation());
			// FVector MakeVector3D = (WidgetOwner->GetActorLocation() +
			// 		WidgetOwner->GetWidgetComponent()->GetRelativeLocation()) -
			// 	EnemyParty[BattleArrayIndex]->GetActorLocation();

			// UKismetSystemLibrary::MoveComponentTo(WidgetOwner->GetWidgetComponent(),
			//                                       FVector(100.f, 0.0f, 0.0f),
			//                                       FRotator(0, 0, 0),
			//                                       false,
			//                                       false,
			//                                       2.0f,
			//                                       false,
			//                                       EMoveComponentAction::Move,
			//                                       FLatentActionInfo()
			// );

			UE_LOG(LogTemp, Warning, TEXT("%d"), BattleArrayIndex);
			TargetEnemy = (*EnemyParty)[BattleArrayIndex];
			StartSmoothRotateToTarget(TargetEnemy);
		}
	}
}

void UTargetingWidget::Input_ConfirmStarted()
{
	if (GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->IsA(ATBC_PlayerBase::StaticClass()))
	{
		UTurnComponent* TurnOrderComponent = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->TurnComponent;
		TurnOrderComponent->Set_Target(TargetEnemy);
		if (CurrentTurnPlayer)
		{
			CurrentTurnPlayer->SpringArmComponent->SetRelativeRotation(CurrentTurnPlayer->SpringArmRotator);
		}

		if (CurrentTurnPlayer->CurrentSkill != nullptr)
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->ClearWidgetStack();
			CurrentTurnPlayer->StatusComponent->DecreaseSp(CurrentTurnPlayer->CurrentSkill->GetSkillInfo().SkillCost);
			GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->BattleCameraManager->Sequence_SummonPersona(CurrentTurnPlayer);

			FGameplayTag WidgetTag = FGameplayTag::RequestGameplayTag("Widget.Battle.NamePlate.PlayerSkill");
			if (UPopupNamePlateWidget* MakeWidget = Cast<UPopupNamePlateWidget>(
				GetWorld()->GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(
					WidgetTag)))
			{
				
				FName MakeSkillName = CurrentTurnPlayer->CurrentSkill->GetSkillInfo().SkillName;
				MakeWidget->SetNamePlate(FText::FromName(MakeSkillName));
				MakeWidget->AddViewportEvent();
				
			}

			if (PartyPanelBattleSPUpdate.IsBound())
			{
				PartyPanelBattleSPUpdate.Broadcast();
			}
			
			
			return;
		}

		else if (CurrentTurnPlayer->CurrentSkill == nullptr)
		{
			TurnOrderComponent->AttackCommand();
			return;
		}
	}
}

void UTargetingWidget::Input_CancelStarted()
{
	EndSkillTargeting();
}
