// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BgmManager.generated.h"

UCLASS()
class PERSONA3REROAD_API ABgmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABgmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void PlayBGM(FName SoundName, float FadeTime);

protected:
	UPROPERTY();
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, Category=Audio)
	TMap<FName,TObjectPtr<USoundBase>> Sounds;
	
	
};
