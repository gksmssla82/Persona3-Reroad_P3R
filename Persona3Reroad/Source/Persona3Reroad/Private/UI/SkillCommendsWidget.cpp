// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillCommendsWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Persona/PersonaBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/RetainerBox.h"
#include "Components/StatusComponent.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/WidgetComponent.h"
#include "Data/UIData/SkillCommendsWidgetDataAsset.h"
#include "DSP/Delay.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/PersonaGameInstance.h"
#include "System/WidgetInstanceSubsystem.h"
#include "UI/SkillListWidget.h"
#include "UI/TargetingWidget.h"


USkillCommendsWidget::USkillCommendsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentVerticalSkillListBoxIndex = 0;
}

void USkillCommendsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<USkillCommendsWidgetDataAsset>(BaseDataAsset);
	}
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
			{
				//Up
				if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Up"))
				{
					EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
													   &USkillCommendsWidget::Input_UpStarted);
				}
				//Down
				if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Down"))
				{
					EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
													   &USkillCommendsWidget::Input_DownStarted);
				}
				//Confirm
				if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Confirm"))
				{
					EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
													   &USkillCommendsWidget::Input_ConfirmStarted);
				}
				//PersonaStatus
				if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("PersonaStatus"))
				{
					EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
													   &USkillCommendsWidget::Input_PersonaStatusStarted);
				}
				//Cancel
				if (UInputAction* InputActionAttack = WidgetDataAsset->FindInputAction("Cancel"))
				{
					EnhancedInputComponent->BindAction(InputActionAttack, ETriggerEvent::Started, this,
													   &USkillCommendsWidget::Input_CancelStared);
				}
			}
		}
	}

	SkillDescriptionArray.Add(SkillDescription_0);
	SkillDescriptionArray.Add(SkillDescription_1);
	SkillDescriptionArray.Add(SkillDescription_2);

	// if (PersonaRetainerBox)
	// {
	// 	UMaterialInstanceDynamic* MakeMID = PersonaRetainerBox->GetEffectMaterial();
	// 	PersonaMaterials = MakeMID;
	// 	PersonaRetainerBox->SetEffectMaterial(PersonaMaterials);
	// }

	

}

void USkillCommendsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillCommendsWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("Stance.SelectCommend"));
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]->StatusComponent->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("Stance.SelectSkill"));

	if (GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0])
	{
		TurnOrder = Cast<ATBC_PlayerBase>(GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]);
	}
	
	CurrentVerticalSkillListBoxIndex = 0;
	
	SetSkillCommends();
	SetSkillInfo(CurrentVerticalSkillListBoxIndex);
	
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}


void USkillCommendsWidget::SetSkillCommends()
{
	
	if (WidgetDataAsset)
	{
		if (APersonaBase* MakePersona = TurnOrder->CurrentPersona)
		{
			if (PersonaName)
			{
				SetPersonaImage(MakePersona->PersonaName);
				PersonaName->SetText(FText::FromName(MakePersona->PersonaName));
			}
			TArray<USkillBase*> MakeSkillArray = MakePersona->SkillList;
			if (TSubclassOf<USkillListWidget> MakeSkillLIst = WidgetDataAsset->GetSkillListWidgetClass())
			{
				VerticalSkillListBox->ClearChildren();
				for (int32 i = 0; i < MakeSkillArray.Num(); i++)
				{
					if (USkillListWidget* MakeSkillList = CreateWidget<USkillListWidget>(this, MakeSkillLIst))
					{
						MakeSkillList->SetSkillType(MakeSkillArray[i]->GetSkillInfo().SkillElement);
						MakeSkillList->SetSkillName(FText::FromName(MakeSkillArray[i]->GetSkillInfo().SkillName));
						MakeSkillList->SetCost(FMath::FloorToInt32(MakeSkillArray[i]->GetSkillInfo().SkillCost));
						MakeSkillList->PlayWidgetAnim(ESkillListAnimType::Hidden);
						
						VerticalSkillListBox->AddChild(MakeSkillList);
						if (UVerticalBoxSlot* MakeSlot = Cast<UVerticalBoxSlot>(
							VerticalSkillListBox->GetChildAt(i)->Slot))
						{
							MakeSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, -13.0f));
						}
					}
				}
			}
		}
	}
}

void USkillCommendsWidget::SetSkillInfo(const int32& Index)
{
	if (APersonaBase* MakePersona = TurnOrder->CurrentPersona)
	{
		TArray<FName> MakeArray = MakePersona->SkillList[Index]->GetSkillInfo().SkillExplain;

		for (int32 i = 0; i < SkillDescriptionArray.Num(); i++)
		{
			if (MakeArray.IsValidIndex(i))
			{
				SkillDescriptionArray[i]->SetText(FText::FromName(MakeArray[i]));
			}
			else
			{
				SkillDescriptionArray[i]->SetText(FText::GetEmpty());
			}
		}
	}
}

void USkillCommendsWidget::SetPersonaImage(const FName& InName)
{
	if (WidgetDataAsset)
	{
		if (UTexture2D* MakeTexture = WidgetDataAsset->FindPersonaTexture(InName))
		{
			PersonaBak->SetBrushFromTexture(MakeTexture);

			if (PersonaRetainerBox)
			{
				PersonaRetainerBox->GetEffectMaterial()->SetTextureParameterValue(FName("Param"), MakeTexture);
				PersonaRetainerBox->GetEffectMaterial()->SetTextureParameterValue(FName("ParamMask"), MakeTexture);
			}


			// if (PersonaMaterials)
			// {
			// 	PersonaMaterials->SetTextureParameterValue(FName("Param"), MakeTexture);
			// 	PersonaMaterials->SetTextureParameterValue(FName("ParamMask"), MakeTexture);
			// }
		}
	}
}


void USkillCommendsWidget::PlayAnim_CreateSkillList()
{
	if (VerticalSkillListBox)
	{
		for (int32 i = 0; i < VerticalSkillListBox->GetChildrenCount(); i++)
		{
			if (USkillListWidget* MakeSkillList = Cast<USkillListWidget>(VerticalSkillListBox->GetChildAt(i)))
			{
				int32 MakeIndex = CurrentVerticalSkillListBoxIndex;
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle,
				                                       [i,MakeSkillList,MakeIndex]()
				                                       {
				                                       		MakeSkillList->SetVisibility(ESlateVisibility::Visible);
					                                       if (i == MakeIndex)
					                                       {
						                                       MakeSkillList->PlayWidgetAnim(
							                                       ESkillListAnimType::CreateSelect);
					                                       }
					                                       else
					                                       {
						                                       MakeSkillList->
							                                       PlayWidgetAnim(ESkillListAnimType::Create);
					                                       }
				                                       },
				                                       0.01f + 0.07f * i,
				                                       false);
			}
		}
	}
}



void USkillCommendsWidget::Input_UpStarted()
{
	if (VerticalSkillListBox && CurrentVerticalSkillListBoxIndex > 0)
	{
		CurrentVerticalSkillListBoxIndex--;
		for (int32 i = 0; i < VerticalSkillListBox->GetChildrenCount(); i++)
		{
			if (USkillListWidget* MakeSkillList = Cast<USkillListWidget>(VerticalSkillListBox->GetChildAt(i)))
			{
				if (i == CurrentVerticalSkillListBoxIndex)
				{
					MakeSkillList->PlayWidgetAnim(ESkillListAnimType::UpSelect);
					UGameplayStatics::PlaySound2D(GetWorld(),SkillPickSfx);
				}
				else
				{
					MakeSkillList->PlayWidgetAnim(ESkillListAnimType::Reset);
				}
			}
		}
		SetSkillInfo(CurrentVerticalSkillListBoxIndex);
	}
}

void USkillCommendsWidget::Input_DownStarted()
{
	if (VerticalSkillListBox && CurrentVerticalSkillListBoxIndex < VerticalSkillListBox->GetChildrenCount() - 1)
	{
		CurrentVerticalSkillListBoxIndex++;
		for (int32 i = 0; i < VerticalSkillListBox->GetChildrenCount(); i++)
		{
			if (USkillListWidget* MakeSkillList = Cast<USkillListWidget>(VerticalSkillListBox->GetChildAt(i)))
			{
				if (i == CurrentVerticalSkillListBoxIndex)
				{
					MakeSkillList->PlayWidgetAnim(ESkillListAnimType::DownSelect);
					UGameplayStatics::PlaySound2D(GetWorld(),SkillPickSfx);
				}
				else
				{
					MakeSkillList->PlayWidgetAnim(ESkillListAnimType::Reset);
				}
			}
		}
		SetSkillInfo(CurrentVerticalSkillListBoxIndex);
	}
}


void USkillCommendsWidget::Input_ConfirmStarted()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red,
		                                 FString::Printf(TEXT("Current Index : %d"), CurrentVerticalSkillListBoxIndex));
	}
	if (UUserWidget* MakeWidget = GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetTargetController()->
	                                                 GetWidgetComponent()->GetWidget())
	{
		if (UTargetingWidget* MakeTargetingWidget = Cast<UTargetingWidget>(MakeWidget))
		{
			if (TurnOrder && TurnOrder->CurrentPersona)
			{
				// 스킬 사용가능한지? 코드인데 조건분기 가능?
				//if(TurnOrder->CurrentPersona->SkillList[CurrentVerticalSkillListBoxIndex]->CanUseSkill(TurnOrder->StatusComponent, TurnOrder->CurrentPersona->CurrentSkill)
				
					TurnOrder->CurrentSkill = TurnOrder->CurrentPersona->SkillList[CurrentVerticalSkillListBoxIndex];
					TurnOrder->CurrentSkill->Set_Element(TurnOrder);
				UGameplayStatics::PlaySound2D(GetWorld(),SelectSkillSfx);
				//
			}
			
			MakeTargetingWidget->StartSkillTargeting();
			this->RemoveViewportEvent();
		}
	}
}

void USkillCommendsWidget::Input_PersonaStatusStarted()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,FString::Printf(TEXT("Current Index : %d") , CurrentVerticalSkillListBoxIndex));
	}
}

void USkillCommendsWidget::Input_CancelStared()
{
	if (UPersonaGameInstance* MakeGameInstance = Cast<UPersonaGameInstance>(GetGameInstance()))
	{
		if (UWidgetInstanceSubsystem* MakeSubsystem = MakeGameInstance->GetSubsystem<UWidgetInstanceSubsystem>())
		{
			MakeSubsystem->PopWidget();
			UGameplayStatics::PlaySound2D(GetWorld(),SkillBackSfx);
		}
	}
}
