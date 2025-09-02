// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Combet/BaseCombatWidgetActor.h"

#include "Components/WidgetComponent.h"
#include "UI/BaseCombatWidget.h"

// Sets default values
ABaseCombatWidgetActor::ABaseCombatWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	RootComponent = WidgetComponent;
	
	

}

// Called when the game starts or when spawned
void ABaseCombatWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}



