// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUIWidget.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "System/PersonaGameInstance.h"
#include "System/WidgetInstanceSubsystem.h"

UBaseUIWidget::UBaseUIWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBaseUIWidget::SetBrushFromSprite(UImage* Image, UPaperSprite* Sprite)
{
	if (Image && Sprite)
	{
		Image->SetBrushResourceObject(Sprite);
	}
}

void UBaseUIWidget::SetBrushFromSprite2D(const FUImage2D* Image2D, const FSprite2D* Sprite2D)
{
	if (!Image2D || !Sprite2D)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetBrushFromSprite2D NULL"));
		return;
	}
	SetBrushFromSprite(Image2D->FrontImage, Sprite2D->FrontSprite);
	SetBrushFromSprite(Image2D->BackImage, Sprite2D->BackSprite);
}

void UBaseUIWidget::AddViewportEvent()
{
	this->AddToViewport();
}



void UBaseUIWidget::AddViewportEvent(const int32& InZOrder)
{
	this->AddToViewport(InZOrder);
}

void UBaseUIWidget::RemoveViewportEvent()
{
	this->RemoveFromParent();
}

void UBaseUIWidget::PlayAnim_Hidden()
{
}

float UBaseUIWidget::NormalizeProgressBarPercent(const float Max, const float Current) const
{
	return Current / Max;
}

TArray<int32> UBaseUIWidget::SplitNumberIntoDigits(const int32& State)
{
	TArray<int32> States;
	int32 NumStates = State;

	while (NumStates > 0)
	{
		States.Add(NumStates % 10);
		NumStates /= 10;
	}

	return States;
}

