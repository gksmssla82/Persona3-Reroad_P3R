// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/CameraManager.h"

#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "System/BattleInstanceSubsystem.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_CameraManager(this);
}

void ACameraManager::InitializeSetCamerasRotation()
{
	for (const auto& Camera : Cameras)
	{
		//FName CameraName = Camera.Key;

		if (ACameraActionBase* CameraAction = Camera.Value)
		{
			if (CameraAction == Cameras.FindRef("SkyStart") || CameraAction == Cameras.FindRef("SkyEnd"))
			{
				continue;
			}
			
			CameraAction->InitializeCameraRotation();
		}
	}
}

void ACameraManager::ToStartFromEndCamera(ATBC_CharacterBase* Target, FName StartKey, FName EndKey, float BlendTime) const
{
	if (ACameraActionBase* StartCam = Cameras.FindRef(StartKey))
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepRelative, true);
		
		if (ACameraActionBase* EndCam = Cameras.FindRef((EndKey)))
		{
			StartCam->AttachToActor(Target, AttachmentTransformRules);
			StartCam->SetActorRelativeLocation(FVector::ZeroVector);
			StartCam->SetActorRelativeRotation(StartCam->CameraArmRotation);
			
			EndCam->AttachToActor(Target,AttachmentTransformRules);
			EndCam->SetActorRelativeLocation(FVector::ZeroVector);
			EndCam->SetActorRelativeRotation(EndCam->CameraArmRotation);
			PlayerController->SetViewTarget(StartCam);
			PlayerController->SetViewTargetWithBlend(EndCam, BlendTime);
		}
	}
}

void ACameraManager::ToAttachCameraFromSoket(ATBC_CharacterBase* Target, FName Key, FName SocketName) const
{
	if (ACameraActionBase* AttachCam = Cameras.FindRef(Key))
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepRelative, true);

		AttachCam->AttachToComponent(Target->GetMesh(), AttachmentTransformRules, SocketName);
		AttachCam->SetActorRelativeRotation(FRotator::ZeroRotator);
		AttachCam->SetActorRelativeLocation(FVector::ZeroVector);
		PlayerController->SetViewTargetWithBlend(AttachCam,0.4f);
	}
}

void ACameraManager::CurrntCameraBlendTarget(ATBC_CharacterBase* Target, FName Key, float BlendTime) const
{
	if (ACameraActionBase* NextCam = Cameras.FindRef(Key))
	{
		
		PlayerController->SetViewTargetWithBlend(NextCam, BlendTime);
	}
}

void ACameraManager::PlayerSubAction(ATBC_CharacterBase* Target, FName EndKey, float BlendTime) const
{
	if (ACameraActionBase* MoveCam = Cameras.FindRef(EndKey))
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepRelative, true);
		MoveCam->AttachToActor(Target, AttachmentTransformRules);
		MoveCam->SetActorRelativeRotation(FRotator::ZeroRotator);
		MoveCam->SetActorRelativeLocation(FVector::ZeroVector);
		PlayerController->SetViewTarget(Target);
		PlayerController->SetViewTargetWithBlend(MoveCam,1.5f);
	}
}

void ACameraManager::WorldCameraFromToCamera(FName StartKey, FName EndKey, float BlendTime) const
{
	if (ACameraActionBase* StartCam = Cameras.FindRef(StartKey))
	{
		if (ACameraActionBase* EndCam = Cameras.FindRef(EndKey))
		{
			PlayerController->SetViewTarget(StartCam);
			PlayerController->SetViewTargetWithBlend(EndCam, BlendTime);
		}
	}
}


void ACameraManager::Sequence_BattleStart() const
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("BattleMap_BattleStart"))
	{
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (SequencePlayer)
			SequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}

	
}

void ACameraManager::Sequence_SummonPersona(AActor* Player)
{
	if (!Player)
	{
		return;
	}
	
	
		
		if (!CurrentSequencePlayer || !SummonSequenceActor)
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
			return;
		}

		for (const FMovieSceneBinding& Binding : SummonSequenceAsset->GetMovieScene()->GetBindings())
		{
			if (Binding.GetName().Contains(TEXT("BP_TBC_MainCharacter")))
			{
				TArray<AActor*> BindingActors;
				BindingActors.Add(Player);

				// 최근 엔진에서는 SetBinding(FGuid, const TArray<AActor*>&) 형태만 지원될 수 있음
				SummonSequenceActor->SetBinding(FMovieSceneObjectBindingID(Binding.GetObjectGuid()), BindingActors);
				break;
			}
		}

		CurrentSequencePlayer->Play();
	}

void ACameraManager::Sequence_MainAllOut()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("AllOut_Main"))
	{
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (SequencePlayer)
			SequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}

void ACameraManager::Sequence_YukariAllOut()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("AllOut_Yukari"))
	{
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (SequencePlayer)
			SequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}

void ACameraManager::Sequence_MitsuruAllOut()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("AllOut_Mitsuru"))
	{
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (SequencePlayer)
			SequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}


void ACameraManager::SummonSequenceLoad()
{
	if (SummonSequenceAsset = Sequences.FindRef("SummonPersona"))
	{
		ALevelSequenceActor* SequenceActor = nullptr;
		FMovieSceneSequencePlaybackSettings Settings;
		CurrentSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SummonSequenceAsset,
			Settings,
			SummonSequenceActor);
		
	}
}

void ACameraManager::Sequence_MainVictory()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("Victory_Main"))
	{
		ALevelSequenceActor* SequenceActor;
		VictorySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (VictorySequencePlayer)
			VictorySequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}

void ACameraManager::Sequence_YukariVictory()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("Victory_Yukari"))
	{
		ALevelSequenceActor* SequenceActor;
		VictorySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (VictorySequencePlayer)
			VictorySequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}

void ACameraManager::Sequence_JunpaiVictory()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("Victory_Junpai"))
	{
		ALevelSequenceActor* SequenceActor;
		VictorySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (VictorySequencePlayer)
			VictorySequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}
			

void ACameraManager::Sequence_MituruVictory()
{
	if (ULevelSequence* SequenceAsset = Sequences.FindRef("Victory_Mituru"))
	{
		ALevelSequenceActor* SequenceActor;
		VictorySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			SequenceAsset,
			FMovieSceneSequencePlaybackSettings(),
			SequenceActor
			);

		if (VictorySequencePlayer)
			VictorySequencePlayer->Play();

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Sequence play failed"));
		}
	}
}









