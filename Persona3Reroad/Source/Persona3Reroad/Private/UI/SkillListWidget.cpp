// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkillListWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Data/UIData/SkillListWidgetDataAsset.h"

USkillListWidget::USkillListWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USkillListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (BaseDataAsset)
	{
		WidgetDataAsset = Cast<USkillListWidgetDataAsset>(BaseDataAsset);
	}
}

void USkillListWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillListWidget::SetSkillInfo(const FName& InSkillType, const FName& InCostType, const int32& InCost,
                                    const FText& InText)
{
	// //SkillType
	// SetSkillType(InSkillType);

	//SetCostType
	SetCostType(InCostType);

	//SetCostTextImage
	//SetCostTextImage(InCost, InCostType);

	//SkillName
	SetSkillName(InText);
}


void USkillListWidget::PlayWidgetAnim(const ESkillListAnimType& Anim)
{
	switch (Anim)
	{
	case ESkillListAnimType::Reset:
		if (Reset)
		{
			PlayAnimation(Reset);
		}
		break;
	case ESkillListAnimType::Create:
		if (CreateAnim)
		{
			PlayAnimation(CreateAnim);
		}
		break;
	case ESkillListAnimType::CreateSelect:
		if (CreateSelectAnim)
		{
			PlayAnimation(CreateSelectAnim);
		}
		break;
	case ESkillListAnimType::DownSelect:
		if (DownSelectAnim)
		{
			PlayAnimation(DownSelectAnim);
		}
		break;
	case ESkillListAnimType::UpSelect:
		if (UpSelectAnim)
		{
			PlayAnimation(UpSelectAnim);
		}
		break;
	case ESkillListAnimType::Hidden:
		if (Hidden)
		{
			PlayAnimation(Hidden);
		}
		break;
	default:
		break;
	}
}

void USkillListWidget::SetSkillType(const EElement& InElement)
{
	if (WidgetDataAsset && SkillType)
	{
		if (UPaperSprite* MakeSprite = WidgetDataAsset->FindSkillTypeSprite(InElement))
		{
			SkillType->SetBrushResourceObject(MakeSprite);
		}
	}
}

void USkillListWidget::SetCostType(const FName& Name)
{
	if (WidgetDataAsset && CostType)
	{
		if (UPaperSprite* MakeSprite = WidgetDataAsset->FindCostTypeSprite(Name))
		{
			CostType->SetBrushResourceObject(MakeSprite);
		}
		if (CostColorBox)
		{
			if (const FLinearColor* MakeColor = WidgetDataAsset->FindCostColor(Name))
			{
				CostColorBox->SetColorAndOpacity(*MakeColor);
			}
		}
	}
}



void USkillListWidget::SetCost(const int32& Num)
{
	TArray<int32> CostArray = SplitNumberIntoDigits(Num);
	FLinearColor CostColor;

	if (WidgetDataAsset)
	{
		if (const FLinearColor* MakeColor = WidgetDataAsset->FindCostColor("SP"))
		{
			CostColor = *MakeColor;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SetCostTextImage -> CostColor isNull"));
			return;
		}
	}

	if (WidgetDataAsset && SkillCostTextImageBox)
	{
		SkillCostTextImageBox->ClearChildren();
		for (int32 i = 0; i < CostArray.Num(); i++)
		{
			UImage* MakeImage = NewObject<UImage>(this);
			if (UPaperSprite* MakeSprite = WidgetDataAsset->GetSkillCostSprite(CostArray[i]))
			{
				MakeImage->SetBrushResourceObject(MakeSprite);
				MakeImage->SetColorAndOpacity(CostColor);
				SkillCostTextImageBox->InsertChildAt(0, MakeImage);

				UWidget* ChildWidget = SkillCostTextImageBox->GetChildAt(0);
				if (UImage* ChildImage = Cast<UImage>(ChildWidget))
				{
					UHorizontalBoxSlot* ImageSlot = Cast<UHorizontalBoxSlot>(ChildImage->Slot);
					ImageSlot->SetPadding(FMargin(0.0f, 0.0f, -10.0f, 0.0));
				}
			}
		}
		
	}
}

void USkillListWidget::SetSkillName(const FText& Text)
{
	if (SkillName)
	{
		SkillName->SetText(Text);
	}
}
