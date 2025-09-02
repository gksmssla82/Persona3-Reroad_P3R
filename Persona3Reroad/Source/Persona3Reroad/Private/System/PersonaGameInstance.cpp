// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PersonaGameInstance.h"
#include "System/PersonaAssetManager.h"

UPersonaGameInstance::UPersonaGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPersonaGameInstance::Init()
{
	Super::Init();
	
	UPersonaAssetManager::Initialize();
	UE_LOG(LogTemp, Display, TEXT("AssetManager Class: %s"), *GEngine->AssetManager->GetClass()->GetName());
}

void UPersonaGameInstance::Shutdown()
{
	Super::Shutdown();
}
