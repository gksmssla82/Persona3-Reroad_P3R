// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPS/TPS_FriendBase.h"

#include "AIController.h"
#include "NetworkMessage.h"
#include "Character/TPS/TPS_MainPlayer.h"

ATPS_FriendBase::ATPS_FriendBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void ATPS_FriendBase::BeginPlay()
{
	Super::BeginPlay();
	
	AiController = Cast<AAIController>(GetController());
	
	if (!AiController)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller <UNK>"));
	}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		MainPlayer = Cast<ATPS_MainPlayer>(PC->GetPawn());
	}
	
}

void ATPS_FriendBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Distance = (GetActorLocation() - MainPlayer->GetActorLocation()).Length();
	
	
	if (Distance >= 400 && MainPlayer->FollowPointse.IsValidIndex(FollowIndex))
	{
		FVector TargetLocation = MainPlayer->FollowPointse[FollowIndex]->GetComponentLocation();
		AiController->MoveToLocation(TargetLocation, -1.f);
		
	}
	
	
	
}

void ATPS_FriendBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
