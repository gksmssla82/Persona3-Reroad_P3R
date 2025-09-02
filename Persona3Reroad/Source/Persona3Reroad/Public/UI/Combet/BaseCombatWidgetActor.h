// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCombatWidgetActor.generated.h"

class UWidgetComponent;

UCLASS()
class PERSONA3REROAD_API ABaseCombatWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCombatWidgetActor();

	FORCEINLINE UWidgetComponent* GetWidgetComponent() const{return WidgetComponent;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TObjectPtr<UWidgetComponent> WidgetComponent;


};
