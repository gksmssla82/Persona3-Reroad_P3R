// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/BgmManager.h"

#include "Components/AudioComponent.h"
#include "System/BattleInstanceSubsystem.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

// Sets default values
ABgmManager::ABgmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABgmManager::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent = NewObject<UAudioComponent>(this);
	AudioComponent->bAutoActivate = false;
	AudioComponent->bIsUISound = false;
	AudioComponent->bAllowSpatialization = false;

	AudioComponent->RegisterComponentWithWorld(GetWorld());

	if (USoundBase* FiledBGM = Sounds.FindRef("FieldBGM"))
	{
		PlayBGM("FieldBGM",0.0f);
	}
	
	GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_BgmManager(this);
}

void ABgmManager::PlayBGM(FName SoundName, float FadeTime)
{
	if (!AudioComponent)
	{
		return;
	}

	if (USoundBase* NewSound = Sounds.FindRef(SoundName))
	{
		if (AudioComponent->IsPlaying())
		{
			AudioComponent->FadeOut(FadeTime, 0.0f);
		}

	

		AudioComponent->SetSound(NewSound);
		AudioComponent->FadeIn(FadeTime, 1.0f);
	}
}


