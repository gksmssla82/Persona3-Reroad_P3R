// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/TurnBase/AnimNotifyStateFaceCam.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "System/BattleInstanceSubsystem.h"

UAnimNotifyStateFaceCam::UAnimNotifyStateFaceCam()
{
}

void UAnimNotifyStateFaceCam::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	
	if (!MeshComp) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: MeshComp is null.")); // 디버깅용 로그
		return;
	}

	UWorld* World = MeshComp->GetWorld(); // MeshComp에서 World 가져오기
	if (!World) // World가 유효한지 체크
	{
		
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: World from MeshComp is null. (Likely Editor Preview)")); // 디버깅용 로그
		return;
	}

	UGameInstance* GameInstance = World->GetGameInstance(); // World에서 GameInstance 가져오기
	if (!GameInstance) 
	{
		
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: GameInstance is null. (Likely Editor Preview)")); // 디버깅용 로그
		return;
	}

	
	if (UBattleInstanceSubsystem* Subsystem = GameInstance->GetSubsystem<UBattleInstanceSubsystem>())
	{
		
		if (Subsystem->BattleCameraManager)
		{
			if (ATBC_CharacterBase* Character = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
			{
				Subsystem->BattleCameraManager->ToAttachCameraFromSoket(Character,"CameraFace", "FaceCam");
				UE_LOG(LogTemp, Warning, TEXT("페이스켐 실시")); // 이 로그가 찍히면 성공
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: MeshComp owner is not ATBC_CharacterBase or is null.")); // 디버깅용 로그
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: BattleCameraManager is null.")); // 디버깅용 로그
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: BattleInstanceSubsystem not found.")); // 디버깅용 로그
	}
}

void UAnimNotifyStateFaceCam::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp) // MeshComp 자체만 먼저 체크
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: MeshComp is null.")); // 디버깅용 로그
		return;
	}

	UWorld* World = MeshComp->GetWorld(); // MeshComp에서 World 가져오기
	if (!World) // World가 유효한지 체크
	{
		// 이 로그는 에디터 미리보기에서 자주 발생하며, 예상된 동작입니다.
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: World from MeshComp is null. (Likely Editor Preview)")); // 디버깅용 로그
		return;
	}

	UGameInstance* GameInstance = World->GetGameInstance(); // World에서 GameInstance 가져오기
	if (!GameInstance) // <-- 이 부분이 핵심! GameInstance가 유효한지 체크해야 합니다.
	{
		// 이 로그도 에디터 미리보기에서 자주 발생하며, 예상된 동작입니다.
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: GameInstance is null. (Likely Editor Preview)")); // 디버깅용 로그
		return;
	}

	// 이제 World와 GameInstance 모두 유효함이 보장됩니다.
	if (UBattleInstanceSubsystem* Subsystem = GameInstance->GetSubsystem<UBattleInstanceSubsystem>())
	{
		// Subsystem->BattleCameraManager도 안전성을 위해 체크하는 것이 좋습니다.
		if (Subsystem->BattleCameraManager)
		{
			if (ATBC_CharacterBase* Character = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
			{
				Subsystem->BattleCameraManager->CurrntCameraBlendTarget(Character,"EnemyHitEnd", 0.3f);
				UE_LOG(LogTemp, Warning, TEXT("페이스켐 실시")); // 이 로그가 찍히면 성공
			}
			else
			{UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: MeshComp owner is not ATBC_CharacterBase or is null.")); // 디버깅용 로그
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: BattleCameraManager is null.")); // 디버깅용 로그
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotifyFaceCam::Notify: BattleInstanceSubsystem not found.")); // 디버깅용 로그
	}
}
