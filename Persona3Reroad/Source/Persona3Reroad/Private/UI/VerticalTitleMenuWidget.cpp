// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VerticalTitleMenuWidget.h"

#include "EnhancedInputComponent.h"
#include "LevelSequencePlayer.h"
#include "Data/UIData/VerticalMainManuWidgetDataAsset.h"
#include "System/WidgetInstanceSubsystem.h"

UVerticalTitleMenuWidget::UVerticalTitleMenuWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),CurrentButtonIndex(0),bIsPlayedCreateAnim(false),bIsPressedUpDownKey(false)
{
}

void UVerticalTitleMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CurrentButtonIndex = 0;
	SetThisClassArray();
	
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UVerticalMainManuWidgetDataAsset>(BaseDataAsset);
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		{
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				//Up
				if (UInputAction* InputActionUp = WidgetDataAsset->FindInputAction("Up"))
				{
					EnhancedInputComponent->BindAction(InputActionUp, ETriggerEvent::Started, this,
													   &UVerticalTitleMenuWidget::Input_UpStarted);
				}
				//Down
				if (UInputAction* InputActionDown = WidgetDataAsset->FindInputAction("Down"))
				{
					EnhancedInputComponent->BindAction(InputActionDown, ETriggerEvent::Started, this,
													   &UVerticalTitleMenuWidget::Input_DownStarted);
				}
				//Confirm
				if (UInputAction* InputActionConfirm = WidgetDataAsset->FindInputAction("Confirm"))
				{
					EnhancedInputComponent->BindAction(InputActionConfirm, ETriggerEvent::Started, this,
													   &UVerticalTitleMenuWidget::Input_ConfirmStarted);
				}
				//ExitGame
				if (UInputAction* InputActionExitGame = WidgetDataAsset->FindInputAction("ExitGame"))
				{
					EnhancedInputComponent->BindAction(InputActionExitGame, ETriggerEvent::Started, this,
													   &UVerticalTitleMenuWidget::Input_ExitGameStarted);
				}
			}
		}
	}
}

void UVerticalTitleMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UVerticalTitleMenuWidget::AddViewportEvent()
{
	AddWidgetMappingContext();
	
	if (!bIsPlayedCreateAnim)
	{
		this->AddToViewport();
		if (CreateAnim)
		{
			PlayAnimation(CreateAnim);
			bIsPlayedCreateAnim = true;
		}
	}
}

void UVerticalTitleMenuWidget::RemoveViewportEvent()
{
	RemoveWidgetMappingContext();

	// if (GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetStackLastWidget() == this)
	// {
	// 	this->RemoveFromParent();
	// 	 if (LevelSequence)
	// 	 {
	// 	 	LevelSequence->Stop();
	// 	 }
	// }
	
}

void UVerticalTitleMenuWidget::Input_UpStarted()
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
	}
	bIsPressedUpDownKey = true;
}

void UVerticalTitleMenuWidget::Input_DownStarted()
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
	}
	bIsPressedUpDownKey = true;
}

void UVerticalTitleMenuWidget::Input_ConfirmStarted()
{
	if (OnButtonFunctionArray[CurrentButtonIndex].IsBound())
	{
		OnButtonFunctionArray[CurrentButtonIndex].Execute();
	}
}

void UVerticalTitleMenuWidget::Input_ExitGameStarted()
{
	//게임 종료
}

void UVerticalTitleMenuWidget::OnNewGameEvent()
{
	FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag("Widget.Title.DifficultySelection");

	if (UWidgetInstanceSubsystem* Sub = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>())
	{
		if (UBaseUIWidget* MakeWidget = Sub->FindRegistryWidgetMap(GameplayTag))
		                                                   
		{
			Sub->PushWidget(MakeWidget);
		}
	}
}

void UVerticalTitleMenuWidget::OnLoadGameEvent()
{
	UE_LOG(LogTemp,Warning,TEXT("OnLoadGameEvent"));
}

void UVerticalTitleMenuWidget::OnConfigEvent()
{
	UE_LOG(LogTemp,Warning,TEXT("OnConfigEvent"));
}

void UVerticalTitleMenuWidget::SetThisClassArray()
{
	//Set Button Anim
	ButtonAnimationArray.Add(NewGameAnim);
	ButtonAnimationArray.Add(LoadGameAnim);
	ButtonAnimationArray.Add(ConfigAnim);

	//Set BlueBar Anim
	BlueBarAnimationArray.Add(BlueBar_0To1);
	BlueBarAnimationArray.Add(BlueBar_1To2);
	BlueBarAnimationArray.Add(BlueBar_2To0);

	//Set Delegate
	OnButtonDelegate OnNewGameDelegate;
	OnNewGameDelegate.BindUObject(this,&UVerticalTitleMenuWidget::OnNewGameEvent);
	OnButtonFunctionArray.Add(OnNewGameDelegate);

	OnButtonDelegate OnLoadGameDelegate;
	OnLoadGameDelegate.BindUObject(this,&UVerticalTitleMenuWidget::OnLoadGameEvent);
	OnButtonFunctionArray.Add(OnLoadGameDelegate);

	OnButtonDelegate OnConfigDelegate;
	OnConfigDelegate.BindUObject(this,&UVerticalTitleMenuWidget::OnConfigEvent);
	OnButtonFunctionArray.Add(OnConfigDelegate);
	
	
}

void UVerticalTitleMenuWidget::PlayInputAnimation_Forward()
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

void UVerticalTitleMenuWidget::PlayInputAnimation_Reverse()
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

void UVerticalTitleMenuWidget::PlayButtonAnimation()
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


