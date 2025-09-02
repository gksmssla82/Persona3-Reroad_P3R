// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enum/EnumBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	StateKeyName = "State";
	TargetActorKeyName = "TargetActor";
	RoutePointKeyName = "RoutePoint";

	AiPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AiPerception"));
	AiSenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

	AiSenseConfig_Sight->SightRadius = 800.0f;
	AiSenseConfig_Sight->LoseSightRadius = 1200.0f;
	AiSenseConfig_Sight->PeripheralVisionAngleDegrees = 45.0f;
	AiSenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AiSenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AiSenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AiSenseConfig_Sight->SetMaxAge(3.0f);

	
	AiPerception->ConfigureSense(*AiSenseConfig_Sight);
	AiPerception->SetDominantSense(UAISense_Sight::StaticClass());
	//AiPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnPerceptionUpdated_Actors);
	
	

	SetGenericTeamId(FGenericTeamId(static_cast<uint8>(EObjectType::Enemy)));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

     int a = 4;
	
	if (AiPerception)
	{
		AiPerception->OnPerceptionUpdated.AddDynamic(this,&ABaseAIController::OnPerceptionUpdated_Actors);
	}

	int b = 10;
	
}

EAiState ABaseAIController::Get_CurrentState()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		return StaticCast<EAiState>(BB->GetValueAsEnum(StateKeyName));
	}

	UE_LOG(LogTemp, Error, TEXT("Faild AiController Get_CurrentState!"));
	
	return EAiState::Passive;
}

void ABaseAIController::Set_StatePassive()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAiState::Passive));
	}
}

void ABaseAIController::Set_StateAttacking()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAiState::Attacking));
	}
}

void ABaseAIController::Set_StateInvestigating(FVector Location)
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAiState::Investigating));
		BB->SetValueAsVector(RoutePointKeyName, Location);
	}
}

void ABaseAIController::Set_StateDead()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAiState::Dead));
	}
}

void ABaseAIController::Set_StateFrozen()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAiState::Frozen));
	}
}

void ABaseAIController::HandleSensedSight(AActor* Actor)
{
	EAiState State = Get_CurrentState();
	
	switch (State)
	{
	case EAiState::Passive:
		break;
	case EAiState::Investigating:
		break;
	default:
		return;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* Target = Cast<ACharacter>(Actor); 
	
	if (PlayerCharacter == Target)
	{
		CancelPassiveTimer();
		Set_StateAttacking();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Faild AiController HandleSensedSight!"));
	}
}

void ABaseAIController::OnPerceptionUpdated_Actors(const TArray<AActor*>& UpdateActors)
{
	
	for (AActor* Actor : UpdateActors)
	{
		if (!Actor) continue;
		
		FAIStimulus SightStimulus;
		
		if (CanSenseActor(Actor, UAISense_Sight::StaticClass(), SightStimulus))
		{
			HandleSensedSight(Actor);
		}
	}
}

bool ABaseAIController::CanSenseActor(AActor* Actor, TSubclassOf<UAISense> SenseClass, FAIStimulus& OutStimulus) 
{
	if (!Actor || !SenseClass || !AiPerception)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild CanSenseActor!"));
		return false;
	}
	
	FActorPerceptionBlueprintInfo ActorPerceptionInfo;
	AiPerception->GetActorsPerception(Actor, ActorPerceptionInfo);
	
		for (const auto& Stimuls : ActorPerceptionInfo.LastSensedStimuli)
		{
			if (Stimuls.Type == SenseClass->GetDefaultObject<UAISense>()->GetSenseID() &&
			Stimuls.WasSuccessfullySensed())
			{
				OutStimulus = Stimuls;
				return true;
			}

			if (!Stimuls.WasSuccessfullySensed())
			{
				StartPassiveTimer();
			}
		}
	
	
	UE_LOG(LogTemp, Error, TEXT("Faild Saved OutStimulus!"));
	return false;
}


ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

	//EQS Test Pawn을 제외시키고 HeroCharacter만 체크하기 위한 조건(HeroCharacter GenericTeamID 0)
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		//TeamID가 다르면
		return ETeamAttitude::Hostile;
	}
	
	return ETeamAttitude::Friendly;
}

void ABaseAIController::StartPassiveTimer()
{
	if (GetWorldTimerManager().IsTimerActive(PassiveStateTimerHandle))
		return;

	GetWorldTimerManager().SetTimer(PassiveStateTimerHandle, this, &ABaseAIController::Set_StatePassive, PassiveStateTimer, false);
}

void ABaseAIController::CancelPassiveTimer()
{
	if (GetWorldTimerManager().IsTimerActive(PassiveStateTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(PassiveStateTimerHandle);
	}
}

void ABaseAIController::SetStateTimer()
{
}
