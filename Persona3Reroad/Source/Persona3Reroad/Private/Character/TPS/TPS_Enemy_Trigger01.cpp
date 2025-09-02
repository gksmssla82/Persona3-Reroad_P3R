// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPS/TPS_Enemy_Trigger01.h"

#include "GameplayTagsManager.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Managers/BgmManager.h"
#include "Object/BattlePostion.h"
#include "Object/EnemyBattlePositionAxis.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"

ATPS_Enemy_Trigger01::ATPS_Enemy_Trigger01(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	BattleTiggerComponent = CreateDefaultSubobject<UBattleTriggerComponent>(TEXT("BattleTriggerComponent"));
	
}

void ATPS_Enemy_Trigger01::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATPS_Enemy_Trigger01::OnCapsuleBeginOverlap);
}

void ATPS_Enemy_Trigger01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATPS_Enemy_Trigger01::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}




void ATPS_Enemy_Trigger01::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("PlayerWeapon"))
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_CurrentTriggerEnemy(this);

		GetWorld()->GetWorldSettings()->SetTimeDilation(0.0f);

		UE_LOG(LogTemp, Warning, TEXT("FTicker 등록됨"));

		TWeakObjectPtr<ATPS_Enemy_Trigger01> WeakThis = this;

		FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateLambda([WeakThis](float DeltaTime)
			{
				if (WeakThis.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("BattleReady 호출됨"));
					WeakThis->BattleReady();
				}
				return false;
			}),
			BattleReadyTime
		);


		
		FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Widget.Transition.InTurnBattle"));
		
		UBaseUIWidget* Widget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag);
		if (Widget)
		{
			Widget->AddViewportEvent();
		}

		GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->BattleBGMManager->PlayBGM("BattleBGM",5.0f);

	}

}

void ATPS_Enemy_Trigger01::Set_Enemy()
{
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->EnemyBattlePositionAxis->Spawn_BattlePositionAndEnemy(EnemyType, EnemyCount);
}

void ATPS_Enemy_Trigger01::BattleReady()
{
	
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.0f);
	
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
{
	GetWorld()->GetTimerManager().SetTimer(
		EnemyDestroyTimerHandle,
		[this]() { Destroy(); },
		5.0f,
		false
	);
});
}


