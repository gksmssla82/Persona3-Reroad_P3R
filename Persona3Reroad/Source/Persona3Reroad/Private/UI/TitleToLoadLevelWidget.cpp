// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleToLoadLevelWidget.h"

#include "Kismet/GameplayStatics.h"

UTitleToLoadLevelWidget::UTitleToLoadLevelWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UTitleToLoadLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UTitleToLoadLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTitleToLoadLevelWidget::AddViewportEvent()
{
	Super::AddViewportEvent();
	if (CreateAnim)
	{
		PlayAnimation(CreateAnim);
	}
}

void UTitleToLoadLevelWidget::RemoveViewportEvent()
{
	Super::RemoveViewportEvent();
	// if (RemoveAnim)
	// {
	// 	PlayAnimation(RemoveAnim);
	// }
}

void UTitleToLoadLevelWidget::OnLevelLoaded()
{
	// FLatentActionInfo LatentInfo;
	// LatentInfo.CallbackTarget = this;
	// LatentInfo.ExecutionFunction = FName("RemoveViewportEvent");
	// LatentInfo.Linkage = 0;
	// LatentInfo.UUID = __LINE__;
	//
	// if (APlayerController* PC = GetOwningPlayer())
	// {
	// 	UGameplayStatics::UnloadStreamLevel(this, FName("MainMemu"), LatentInfo, false);
	// }
	RemoveViewportEvent();
}

void UTitleToLoadLevelWidget::FadeInEvent()
{
	// FLatentActionInfo LatentInfo;
	// LatentInfo.CallbackTarget = this;
	// LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
	// LatentInfo.Linkage = 0;
	// LatentInfo.UUID = __LINE__;
	//
	// if (APlayerController* PC = GetOwningPlayer())
	// {
	// 	UGameplayStatics::LoadStreamLevel(PC, FName("Tartarus"), true, false, LatentInfo);
	// }
	UGameplayStatics::OpenLevel(this, FName("Tartarus"));
	
}
