// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Combet/TargetingCombatWidgetActor.h"

#include "Components/WidgetComponent.h"
#include "UI/TargetingWidget.h"

ATargetingCombatWidgetActor::ATargetingCombatWidgetActor()
	:Super()
{
	
}

void ATargetingCombatWidgetActor::BeginPlay()
{
	Super::BeginPlay();

	if (UTargetingWidget* MakeWidget= Cast<UTargetingWidget>(WidgetComponent->GetWidget()))
	{
		MakeWidget->SetOwner(this);
	}
}
