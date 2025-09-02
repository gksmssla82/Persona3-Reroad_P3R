// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleOutTransitionWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/BgmManager.h"
#include "System/BattleInstanceSubsystem.h"
#include "System/WidgetInstanceSubsystem.h"

UBattleOutTransitionWidget::UBattleOutTransitionWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UBattleOutTransitionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UBattleOutTransitionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBattleOutTransitionWidget::AddViewportEvent()
{
	Super::AddViewportEvent();

	
	
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

void UBattleOutTransitionWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	//뷰포트만 제거
}

void UBattleOutTransitionWidget::FadeOutEvent()
{
	
	//배틀결과 나오고 버튼 클릭하면 화면이 가려진 뒤에 실행될 함수
	//여기에 배틀이 끝나고 원래 맵으로 돌아가도록 하면 될듯?
	
	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->EndBattle();

	//여기 위에 쓰심 됩니다.
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->ClearTransitionWidget();

	
	
	GetGameInstance()->GetSubsystem<UWidgetInstanceSubsystem>()->AddViewportEventCurrentLevelWidgetArray();
}
