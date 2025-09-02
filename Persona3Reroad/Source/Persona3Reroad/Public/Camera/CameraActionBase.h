// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraActionBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PERSONA3REROAD_API ACameraActionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraActionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InitializeCameraRotation();
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

public:
	UPROPERTY(BlueprintReadWrite, Category=Potion)
	FRotator CameraArmRotation;
	UPROPERTY(BlueprintReadWrite, Category=Potion)
	FVector CameraArmLocation;
	UPROPERTY(BlueprintReadWrite,  Category=Potion)
	FRotator CameraRotation;
	UPROPERTY(BlueprintReadWrite,  Category=Potion)
	FVector CameraLocation;
	

};
