// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Combet/FloatingCombatWidgetActor.h"

#include "Components/WidgetComponent.h"
#include "UI/CombatDamageGroupWidget.h"

AFloatingCombatWidgetActor::AFloatingCombatWidgetActor()
	:Super()
{
}

void AFloatingCombatWidgetActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WidgetComponent->GetWidget())
	{
		CombatWidget = Cast<UCombatDamageGroupWidget>(WidgetComponent->GetWidget());
	}
}

void AFloatingCombatWidgetActor::Init_DamageGroup(const int32& InDamage, const bool& Weak)
{
	if (CombatWidget)
	{
		CombatWidget->Init_CombatDamageGroup(InDamage,Weak);
	}
}


void AFloatingCombatWidgetActor::BeginPlay()
{
	Super::BeginPlay();
}
