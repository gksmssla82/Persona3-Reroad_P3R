// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyPanelBattleWidget.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/StatusComponent.h"
#include "Components/TurnComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/UIData/PartyPanelBattleDataAsset.h"
#include "System/WidgetInstanceSubsystem.h"
#include "UI/TargetingWidget.h"


UPartyPanelBattleWidget::UPartyPanelBattleWidget(const FObjectInitializer& ObjectInitializer)

	: Super(ObjectInitializer)
{
}


void UPartyPanelBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UPartyPanelBattleDataAsset>(BaseDataAsset);
	}

	FaceGroup = FUImage3D(Face, FaceShadowLeft, FaceShadowRight);

	HPTextImageGroup.Add(FUImage2D(HPText_1sPlace, HPText_1sPlaceOutline));
	HPTextImageGroup.Add(FUImage2D(HPText_10sPlace, HPText_10sPlaceOutline));
	HPTextImageGroup.Add(FUImage2D(HPText_100sPlace, HPText_100sPlaceOutline));

	SPTextImageGroup.Add(FUImage2D(SPText_1sPlace, SPText_1sPlaceOutline));
	SPTextImageGroup.Add(FUImage2D(SPText_10sPlace, SPText_10sPlaceOutline));
	SPTextImageGroup.Add(FUImage2D(SPText_100sPlace, SPText_100sPlaceOutline));

	
}

void UPartyPanelBattleWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPartyPanelBattleWidget::Init_PartyPanelBattle(const TObjectPtr<ATBC_PlayerBase>& InOwner)
{
	if (InOwner)
	{
		OwnerCharacter = InOwner;
		if (WidgetDataAsset)
		{
			SetDefaultFace();
			UpdateTextStatus();
			UpdateStatusBar();
			PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType::Hidden);
		}

		//미츠루 사이즈
		if (OwnerCharacter->StatusComponent->Get_Status().CharacterName == "Mitsuru")
		{
			
			FSlateBrush Brush = Face->GetBrush();
			Brush.ImageSize = FVector2D(247.0f, 191.0f);
			Face->SetBrush(Brush);
			if (UCanvasPanelSlot* MakeSlot1 = Cast<UCanvasPanelSlot>(Face->Slot))
			{
				MakeSlot1->SetOffsets(FMargin(15.0f,5.0f,0.0f,0.0f));
			}
			

			FSlateBrush Brush1 = FaceShadowLeft->GetBrush();
			Brush1.ImageSize = FVector2D(247.0f, 191.0f);
			FaceShadowLeft->SetBrush(Brush1);
			if (UCanvasPanelSlot* MakeSlot2 = Cast<UCanvasPanelSlot>(FaceShadowLeft->Slot))
			{
				MakeSlot2->SetOffsets(FMargin(15.0f,5.0f,0.0f,0.0f));
			}

			FSlateBrush Brush2 = FaceShadowRight->GetBrush();
			Brush2.ImageSize = FVector2D(247.0f, 191.0f);
			FaceShadowRight->SetBrush(Brush2);
			if (UCanvasPanelSlot* MakeSlot3 = Cast<UCanvasPanelSlot>(FaceShadowRight->Slot))
			{
				MakeSlot3->SetOffsets(FMargin(15.0f,5.0f,0.0f,0.0f));
			}
		}

		//Widget Turn Start End Animation
		OwnerCharacter->TurnComponent->OnWidgetTurnStarted.AddDynamic(this, &UPartyPanelBattleWidget::InTurnOrderEvent);
		OwnerCharacter->TurnComponent->OnWidgetTurnEnded.AddDynamic(this, &UPartyPanelBattleWidget::OutTurnOrderEvent);

		//Widget Hit Animation
		OwnerCharacter->StatusComponent->OnHitDeleGateNoParam.AddDynamic(this,&UPartyPanelBattleWidget::OnHitEvent);

		//Widget SPUpdate
		if (GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetTargetController())
		{
			if (UTargetingWidget* MakeWidget = Cast<UTargetingWidget>(GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->GetTargetController()->GetWidgetComponent()->GetWidget()))
			{
				MakeWidget->PartyPanelBattleSPUpdate.AddDynamic(this,&UPartyPanelBattleWidget::UpdateTextStatus);
				MakeWidget->PartyPanelBattleSPUpdate.AddDynamic(this,&UPartyPanelBattleWidget::UpdateStatusBar);
			}
				
		}
	}
	

	
}

void UPartyPanelBattleWidget::PlayPartyPanelBattleAnim(const EPartyPanelBattleAnimType AnimType)
{
	switch (AnimType)
	{
	case EPartyPanelBattleAnimType::Create:
		if (CreateAnim)
		{
			PlayAnimation(CreateAnim);
		}
		break;
	case EPartyPanelBattleAnimType::InTurnOrder:
		if (InTurnOrder)
		{
			PlayAnimation(InTurnOrder);
		}
		break;
	case EPartyPanelBattleAnimType::OutTurnOrder:
		if (OutTurnOrder)
		{
			PlayAnimation(OutTurnOrder);
		}
		break;
	case EPartyPanelBattleAnimType::Hit:
		if (HitAnim)
		{
			PlayAnimation(HitAnim);
		}
		break;
	case EPartyPanelBattleAnimType::Hidden:
		if (OutTurnOrder)
		{
			PlayAnimation(OutTurnOrder);
		}
		if (Hidden)
		{
			PlayAnimation(Hidden);
		}
		break;
	default:
		break;
	}
}

void UPartyPanelBattleWidget::OnHitEvent()
{
	PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType::Hit);
}

void UPartyPanelBattleWidget::InTurnOrderEvent()
{
	PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType::InTurnOrder);
}

void UPartyPanelBattleWidget::OutTurnOrderEvent()
{
	PlayPartyPanelBattleAnim(EPartyPanelBattleAnimType::OutTurnOrder);
}


void UPartyPanelBattleWidget::SetFace(UPaperSprite* Sprite)
{
	if (Sprite)
	{
		SetBrushFromSprite(FaceGroup.FrontImage, Sprite);
		SetBrushFromSprite(FaceGroup.LeftImage, Sprite);
		SetBrushFromSprite(FaceGroup.RightImage, Sprite);
	}
}

void UPartyPanelBattleWidget::SetDefaultFace()
{
	if (OwnerCharacter)
	{
		FName MakeName = OwnerCharacter->StatusComponent->Get_Status().CharacterName;
		if (FPartyPanelBattleFaceGroup* MakeSprite = WidgetDataAsset->FindPartyFaceGroup(MakeName))
		{
			if (MakeSprite->DefaultFace)
			{
				SetFace(MakeSprite->DefaultFace);
			}
		}
	}
}

void UPartyPanelBattleWidget::SetHitFace()
{
	if (OwnerCharacter)
	{
		FName MakeName = OwnerCharacter->StatusComponent->Get_Status().CharacterName;
		if (FPartyPanelBattleFaceGroup* MakeSprite = WidgetDataAsset->FindPartyFaceGroup(MakeName))
		{
			if (MakeSprite->DefaultFace)
			{
				SetFace(MakeSprite->HitFace);
			}
		}
	}
}

void UPartyPanelBattleWidget::HitAnimStart()
{
	SetHitFace();
	UpdateTextStatus();
	UpdateStatusBar();
}

void UPartyPanelBattleWidget::HitAnimEnd()
{
	SetDefaultFace();
}

void UPartyPanelBattleWidget::UpdateTextStatus()
{
	if (OwnerCharacter)
	{
		//HP
		int32 HP = OwnerCharacter->StatusComponent->Get_Status().CurrentHp;
		TArray<int32> HPDigits = SplitNumberIntoDigits(HP);

		for (int32 i = 0; i < HPTextImageGroup.Num(); i++)
		{
			if (HPDigits.IsValidIndex(i))
			{
				if (const FSprite2D* MakeSprite2D = WidgetDataAsset->FindStateText(HPDigits[i]))
				{
					HPTextImageGroup[i].SetMemberFromSprite2D(MakeSprite2D);
					if (const FLinearColor* MakeLinearColor = WidgetDataAsset->FindColor("Default"))
					{
						HPTextImageGroup[i].FrontImage->SetColorAndOpacity(*MakeLinearColor);
					}
				}
			}
			else
			{
				if (const FSprite2D* MakeSprite2D = WidgetDataAsset->FindStateText(0))
				{
					HPTextImageGroup[i].SetMemberFromSprite2D(MakeSprite2D);
					if (const FLinearColor* MakeLinearColor = WidgetDataAsset->FindColor("ZeroPadding"))
					{
						HPTextImageGroup[i].FrontImage->SetColorAndOpacity(*MakeLinearColor);
					}
				}
			}

			//SP
			int32 SP = OwnerCharacter->StatusComponent->Get_Status().CurrentSp;
			TArray<int32> SPDigits = SplitNumberIntoDigits(SP);

			for (int32 j = 0; j < SPTextImageGroup.Num(); j++)
			{
				if (SPDigits.IsValidIndex(j))
				{
					if (const FSprite2D* MakeSprite2D = WidgetDataAsset->FindStateText(SPDigits[j]))
					{
						SPTextImageGroup[j].SetMemberFromSprite2D(MakeSprite2D);
						if (const FLinearColor* MakeLinearColor = WidgetDataAsset->FindColor("Default"))
						{
							SPTextImageGroup[j].FrontImage->SetColorAndOpacity(*MakeLinearColor);
						}
					}
				}
				else
				{
					if (const FSprite2D* MakeSprite2D = WidgetDataAsset->FindStateText(0))
					{
						SPTextImageGroup[j].SetMemberFromSprite2D(MakeSprite2D);
						if (const FLinearColor* MakeLinearColor = WidgetDataAsset->FindColor("ZeroPadding"))
						{
							SPTextImageGroup[j].FrontImage->SetColorAndOpacity(*MakeLinearColor);
						}
					}
				}
			}
		}
	}
}

void UPartyPanelBattleWidget::UpdateStatusBar()
{
	if (OwnerCharacter)
	{
		FStatus MakeStatus = OwnerCharacter->StatusComponent->Get_Status();
		SetHPBarPercent(MakeStatus.MaxHp,MakeStatus.CurrentHp);
		SetSPBarPercent(MakeStatus.MaxSp,MakeStatus.CurrentSp);
	}
}


