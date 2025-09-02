// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PressAnyButtonWidget.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Data/UIData/PressAnyButtonWidgetDataAsset.h"

UPressAnyButtonWidget::UPressAnyButtonWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPressAnyButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UPressAnyButtonWidgetDataAsset>(BaseDataAsset);
	}

	 if (APlayerController* PC = GetOwningPlayer())
	 {
		 {
		 	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		 	{
		 		//Confirm
		 		if (UInputAction* InputActionConfirm = WidgetDataAsset->FindInputAction("Confirm"))
		 		{
		 			EnhancedInputComponent->BindAction(InputActionConfirm, ETriggerEvent::Started, this,
														&UPressAnyButtonWidget::Input_ConfirmStarted);
		 		}
		 	}
		 }
	 }
		
		
}

void UPressAnyButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
	
}

void UPressAnyButtonWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
}

void UPressAnyButtonWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

void UPressAnyButtonWidget::Input_ConfirmStarted()
{
	if (RemoveAnim)
	{
		PlayAnimation(RemoveAnim);
	}
	UE_LOG(LogTemp,Warning,TEXT("HI"));
}


