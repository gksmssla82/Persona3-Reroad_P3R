// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor/BossMap_Actor.h"

ABossMap_Actor::ABossMap_Actor()
{	
	bHasPlayed = false; 
	
}

void ABossMap_Actor::Interact_Implementation(AActor* Interactor)
{
	if (!SkeletalMesh)
	{
		return;
	}

	ABossMap_Actor* Trigger = Cast<ABossMap_Actor>(Interactor);

	// 1. 최초 트리거: 애니메이션 재생 요청 (BP에서 처리)
	if (!bHasPlayed)
	{
		bHasPlayed = true;

		
		SkeletalMesh->SetPlayRate(CurrentPlayRate);

		UE_LOG(LogTemp, Warning, TEXT("▶ 최초 트리거, 애니메이션 재생 시작 (속도: %f)"), CurrentPlayRate);
	}
	// 2. 이후 트리거: 속도만 증가
	else if (Trigger && Trigger->MultiplyRate > 0.f)
	{
		CurrentPlayRate *= Trigger->MultiplyRate;
		SkeletalMesh->SetPlayRate(CurrentPlayRate);

		UE_LOG(LogTemp, Warning, TEXT("▶ 속도 증가! 현재 속도: %f"), CurrentPlayRate);
	}
}

void ABossMap_Actor::BeginPlay()
{
	Super::BeginPlay();
	for (AActor* Target : TargetActors)
	{
		if (Target)
		{
			UE_LOG(LogTemp, Warning, TEXT("🔹 TargetActor: %s"), *Target->GetName());
		}
	}
}

void ABossMap_Actor::OnTriggerBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}
	if (AlreadyTriggeredActors.Contains(OtherActor))
	{
		return;
	}
	AlreadyTriggeredActors.Add(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("🔥 OnTriggerBegin called ONCE by: %s"), *OtherActor->GetName());


	for (AActor* Target : TargetActors)
	{
		if (Target && Target->GetClass()->ImplementsInterface(UBase_Interface::StaticClass()))
		{
			IBase_Interface::Execute_Interact(Target, this); // ← self를 Interactor로 넘김
		}
	}
	 
}

void ABossMap_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
