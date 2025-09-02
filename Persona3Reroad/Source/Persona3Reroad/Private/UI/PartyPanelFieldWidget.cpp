// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PartyPanelFieldWidget.h"

#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Components/CanvasPanelSlot.h"
#include "Data/UIData/PartyPanelFieldDataAsset.h"
#include "System/WidgetInstanceSubsystem.h"

UPartyPanelFieldWidget::UPartyPanelFieldWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPartyPanelFieldWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<UPartyPanelFieldDataAsset>(BaseDataAsset);
	}

	FaceGroup = FUImage3D(Face, FaceShadowLeft, FaceShadowRight);
}

void UPartyPanelFieldWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPartyPanelFieldWidget::AddViewportEvent()
{
	Super::AddViewportEvent();

}

void UPartyPanelFieldWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}

void UPartyPanelFieldWidget::Init_PartyPanelBattle(const TObjectPtr<ATBC_PlayerBase>& InOwner)
{
	if (InOwner)
	{
		OwnerCharacter = InOwner;
		if (WidgetDataAsset)
		{
			FName MakeName = OwnerCharacter->StatusComponent->Get_Status().CharacterName;
			if (UPaperSprite* MakeSprite = WidgetDataAsset->FindFaceMap(MakeName))
			{
				FaceGroup.FrontImage->SetBrushResourceObject(MakeSprite);
				FaceGroup.LeftImage->SetBrushResourceObject(MakeSprite);
				FaceGroup.RightImage->SetBrushResourceObject(MakeSprite);
			}
		}
		if (OwnerCharacter->StatusComponent->Get_Status().CharacterName == "Mitsuru")
		{
			
			FSlateBrush Brush = Face->GetBrush();
			Brush.ImageSize = FVector2D(211.0f, 136.0f);
			Face->SetBrush(Brush);
			if (UCanvasPanelSlot* MakeSlot1 = Cast<UCanvasPanelSlot>(Face->Slot))
			{
				MakeSlot1->SetOffsets(FMargin(20.0f,0.0f,0.0f,0.0f));
			}
			

			FSlateBrush Brush1 = FaceShadowLeft->GetBrush();
			Brush1.ImageSize = FVector2D(211.0f, 136.0f);
			FaceShadowLeft->SetBrush(Brush1);
			if (UCanvasPanelSlot* MakeSlot2 = Cast<UCanvasPanelSlot>(FaceShadowLeft->Slot))
			{
				MakeSlot2->SetOffsets(FMargin(12.0f,5.0f,0.0f,0.0f));
			}

			FSlateBrush Brush2 = FaceShadowRight->GetBrush();
			Brush2.ImageSize = FVector2D(211.0f, 136.0f);
			FaceShadowRight->SetBrush(Brush2);
			if (UCanvasPanelSlot* MakeSlot3 = Cast<UCanvasPanelSlot>(FaceShadowRight->Slot))
			{
				MakeSlot3->SetOffsets(FMargin(28.0f,0.0f,0.0f,0.0f));
			}
		}
	}
}

void UPartyPanelFieldWidget::UpdateStatusBar()
{
	if (OwnerCharacter)
	{
		FStatus MakeStatus = OwnerCharacter->StatusComponent->Get_Status();
		SetHPBarPercent(MakeStatus.MaxHp,MakeStatus.CurrentHp);
		SetSPBarPercent(MakeStatus.MaxSp,MakeStatus.CurrentSp);
	}
}


