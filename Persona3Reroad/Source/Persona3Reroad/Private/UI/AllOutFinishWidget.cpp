// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AllOutFinishWidget.h"

#include "Audio/AudioWidgetSubsystem.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Data/UIData/AllOutFinishDataAsset.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"

UAllOutFinishWidget::UAllOutFinishWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UAllOutFinishWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(BaseDataAsset)
	{
		WidgetDataAsset = Cast<UAllOutFinishDataAsset>(BaseDataAsset);
	}
}

void UAllOutFinishWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
	
void UAllOutFinishWidget::AddViewportEvent()
{
	Super::AddViewportEvent();

	if (WidgetDataAsset && FinishMaterial)
	{
		if (GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0])
		{
			if (UStatusComponent* MakeStatus = GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->TurnOrder[0]
				->StatusComponent)
			{
				if (UMaterialInstance* MakeMaterialInstance = WidgetDataAsset->FindFinishMaterials(
					MakeStatus->Get_Status().CharacterName))
				{
					if (UMaterialInstanceDynamic* MakeMID =UMaterialInstanceDynamic::Create(MakeMaterialInstance,this))
					{
						FinishMaterial->SetBrushFromMaterial(MakeMID);
						if (CreateAnim)
						{
							PlayAnimation(CreateAnim);
							GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->AddTransitionWidget(this);
						}
					}
				}
			}
		}
	}

	
}

void UAllOutFinishWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
}
