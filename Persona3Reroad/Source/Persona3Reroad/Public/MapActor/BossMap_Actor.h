// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "interface/Base_Interface.h"
#include "components/SkeletalMeshComponent.h"
#include "MapActor/Base_Actor.h"
#include "BossMap_Actor.generated.h"

/**
 * 
 */
UCLASS()
class PERSONA3REROAD_API ABossMap_Actor : public ABase_Actor, public IBase_Interface
{
	GENERATED_BODY()
public:
	ABossMap_Actor();
	
	virtual void Interact_Implementation(AActor* Interactor) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float CurrentPlayRate = 1.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	float MultiplyRate = 1.5f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation")
	bool bHasPlayed;

	virtual void OnTriggerBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

private:
		
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TArray<AActor*> TargetActors;
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSet<AActor*> AlreadyTriggeredActors;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
