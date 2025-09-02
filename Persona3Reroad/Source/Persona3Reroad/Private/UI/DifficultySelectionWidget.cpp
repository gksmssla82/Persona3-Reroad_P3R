// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DifficultySelectionWidget.h"

#include "EnhancedInputComponent.h"
#include "Data/UIData/DifficultyWidgetDataAsset.h"
#include "System/WidgetInstanceSubsystem.h"

UDifficultySelectionWidget::UDifficultySelectionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),CurrentButtonIndex(0)
{
}

void UDifficultySelectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CurrentButtonIndex = 0;
	SetThisClassArray();
	
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UDifficultyWidgetDataAsset>(BaseDataAsset);
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			//Up
			if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Up"))
			{
				EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				                                   &UDifficultySelectionWidget::Input_UpStarted);
			}
			//Down
			if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Down"))
			{
				EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				                                   &UDifficultySelectionWidget::Input_DownStarted);
			}
			//Confirm
			if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Confirm"))
			{
				EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				                                   &UDifficultySelectionWidget::Input_ConfirmStarted);
			}
			//Cancel
			if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Cancel"))
			{
				EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
				                                   &UDifficultySelectionWidget::Input_CancelStarted);
			}
		}
	}
}

void UDifficultySelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDifficultySelectionWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	CurrentButtonIndex = 2;
	bIsPressedUpDownKey = false;

	for (int32 i = 0; i < ButtonAnimationArray.Num(); i++)
	{
		if (ButtonAnimationArray[i])
		{
			StopAnimation(ButtonAnimationArray[i]);
		}
	}
	if (RemoveAnim)
	{
		StopAnimation(RemoveAnim);
	}
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}


void UDifficultySelectionWidget::RemoveViewportEvent()
{
	RemoveWidgetMappingContext();
	if (RemoveAnim)
	{
		PlayAnimation(RemoveAnim);
	}
}

void UDifficultySelectionWidget::Input_UpStarted()
{
	if (BlueBarAnimationArray.Num() > 0)
	{
		StopAnimation(ButtonAnimationArray[CurrentButtonIndex]);
		if (CurrentButtonIndex <= 0)
		{
			CurrentButtonIndex = BlueBarAnimationArray.Num() - 1;
		}
		else
		{
			CurrentButtonIndex--;
		}
		PlayInputAnimation_Reverse();
		PlayButtonAnimation();
		bIsPressedUpDownKey = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Index : %d"), CurrentButtonIndex);
}

void UDifficultySelectionWidget::Input_DownStarted()
{
	if (BlueBarAnimationArray.Num() > 0)
	{
		StopAnimation(ButtonAnimationArray[CurrentButtonIndex]);
		PlayInputAnimation_Forward();
		if (CurrentButtonIndex >= BlueBarAnimationArray.Num() - 1)
		{
			CurrentButtonIndex = 0;
		}
		else
		{
			CurrentButtonIndex++;
		}
		PlayButtonAnimation();
		bIsPressedUpDownKey = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Index : %d"), CurrentButtonIndex);
}

void UDifficultySelectionWidget::Input_ConfirmStarted()
{
	if (OnButtonFunctionArray[CurrentButtonIndex].IsBound())
	{
		OnButtonFunctionArray[CurrentButtonIndex].Execute();
	}
}

void UDifficultySelectionWidget::Input_CancelStarted()
{
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->PopWidget();
}

void UDifficultySelectionWidget::PlayInputAnimation_Forward()
{
	if (BlueBarAnimationArray.IsValidIndex(CurrentButtonIndex))
	{
		PlayAnimation(BlueBarAnimationArray[CurrentButtonIndex],
		              0.0f,
		              1,
		              EUMGSequencePlayMode::Forward,
		              1.0f,
		              false);
	}
}

void UDifficultySelectionWidget::PlayInputAnimation_Reverse()
{
	if (BlueBarAnimationArray.IsValidIndex(CurrentButtonIndex))
	{
		PlayAnimation(BlueBarAnimationArray[CurrentButtonIndex],
		              0.0f,
		              1,
		              EUMGSequencePlayMode::Reverse,
		              1.0f,
		              false);
	}
}

void UDifficultySelectionWidget::PlayButtonAnimation()
{
	if (ButtonAnimationArray.IsValidIndex(CurrentButtonIndex))
	{
		PlayAnimation(ButtonAnimationArray[CurrentButtonIndex],
		              0.0f,
		              0,
		              EUMGSequencePlayMode::Forward,
		              1.0f,
		              false);
	}
}

void UDifficultySelectionWidget::OnPeacefulEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("OnPeacefulEvent"));
}

void UDifficultySelectionWidget::OnEasyEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("OnEasyEvent"));
}

void UDifficultySelectionWidget::OnNormalEvent()
{
	if (NormalButtonEventAnim)
	{
		PlayAnimation(NormalButtonEventAnim);	
	}
}

void UDifficultySelectionWidget::OnHardEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("OnHardEvent"));
}

void UDifficultySelectionWidget::OnLunaticEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("OnLunaticEvent"));
}

void UDifficultySelectionWidget::SetThisClassArray()
{
	//Set Button Anim
	ButtonAnimationArray.Add(PeacefulAnim);
	ButtonAnimationArray.Add(EasyAnim);
	ButtonAnimationArray.Add(NormalAnim);
	ButtonAnimationArray.Add(HardAnim);
	ButtonAnimationArray.Add(LunaticAnim);

	//Set BlueBar Anim
	BlueBarAnimationArray.Add(BlueBar0To1);
	BlueBarAnimationArray.Add(BlueBar1To2);
	BlueBarAnimationArray.Add(BlueBar2To3);
	BlueBarAnimationArray.Add(BlueBar3To4);
	BlueBarAnimationArray.Add(BlueBar4To0);

	//Set Delegate
	OnButtonDelegate OnPeacefulDelegate;
	OnPeacefulDelegate.BindUObject(this, &UDifficultySelectionWidget::OnPeacefulEvent);
	OnButtonFunctionArray.Add(OnPeacefulDelegate);

	OnButtonDelegate OnEasyDelegate;
	OnEasyDelegate.BindUObject(this, &UDifficultySelectionWidget::OnEasyEvent);
	OnButtonFunctionArray.Add(OnEasyDelegate);

	OnButtonDelegate OnNormalDelegate;
	OnNormalDelegate.BindUObject(this, &UDifficultySelectionWidget::OnNormalEvent);
	OnButtonFunctionArray.Add(OnNormalDelegate);

	OnButtonDelegate OnHardDelegate;
	OnHardDelegate.BindUObject(this, &UDifficultySelectionWidget::OnHardEvent);
	OnButtonFunctionArray.Add(OnHardDelegate);

	OnButtonDelegate OnLunaticDelegate;
	OnLunaticDelegate.BindUObject(this, &UDifficultySelectionWidget::OnLunaticEvent);
	OnButtonFunctionArray.Add(OnLunaticDelegate);
}

void UDifficultySelectionWidget::OpenNormalLevel()
{
	FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Widget.Transition.ToLoadLevel");
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->FindRegistryWidgetMap(Tag)->AddViewportEvent();
}
