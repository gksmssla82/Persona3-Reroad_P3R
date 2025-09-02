// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseInputWidget.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Data/UIData/BaseInputWidgetDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "System/PersonaGameInstance.h"
#include "System/WidgetInstanceSubsystem.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UBaseInputWidget::UBaseInputWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBaseInputWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetIsFocusable(true);
}

void UBaseInputWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	AddWidgetMappingContext();
}

void UBaseInputWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	RemoveWidgetMappingContext();
}

void UBaseInputWidget::AddWidgetMappingContext()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (UBaseInputWidgetDataAsset* InputWidgetDataAsset = Cast<UBaseInputWidgetDataAsset>(BaseDataAsset))
			{
				if (UInputMappingContext* IMC = InputWidgetDataAsset->GetInputMappingContext())
				{
					{
						Subsystem->AddMappingContext(IMC, 0);
					}
				}
			}
		}
	}
}

void UBaseInputWidget::RemoveWidgetMappingContext()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (UBaseInputWidgetDataAsset* InputWidgetDataAsset = Cast<UBaseInputWidgetDataAsset>(BaseDataAsset))
			{
				if (UInputMappingContext* IMC = InputWidgetDataAsset->GetInputMappingContext())
				{
					{
						Subsystem->RemoveMappingContext(IMC);
						UE_LOG(LogTemp, Warning, TEXT("Removing WidgetMappingContext"));
					}
				}
			}
		}
	}
}

void UBaseInputWidget::OnVisibility()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBaseInputWidget::SetInputModeUIOnly(const bool& bMouseActivate)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC,this);
		PC->bShowMouseCursor = bMouseActivate;
	}
}

void UBaseInputWidget::SetInputModeGameAndUI(const bool& bMouseActivate)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC,this);
		PC->bShowMouseCursor = bMouseActivate;
	}
}

void UBaseInputWidget::SetInputModeGameOnly(const bool& bMouseActivate)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		PC->bShowMouseCursor = bMouseActivate;
	}
}
