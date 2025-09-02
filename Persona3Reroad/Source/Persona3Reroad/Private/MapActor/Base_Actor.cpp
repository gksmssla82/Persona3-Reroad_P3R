// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor/Base_Actor.h"

// Sets default values
ABase_Actor::ABase_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABase_Actor::OnTriggerBegin);
	
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

}

// Called when the game starts or when spawned
void ABase_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABase_Actor::OnTriggerBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called every frame
void ABase_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

