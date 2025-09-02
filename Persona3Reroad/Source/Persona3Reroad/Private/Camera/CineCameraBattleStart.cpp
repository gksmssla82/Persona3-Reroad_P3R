// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CineCameraBattleStart.h"

#include "CineCameraComponent.h"

ACineCameraBattleStart::ACineCameraBattleStart()
{
	UMaterialInterface* PostProcessMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/Material/PS_BattleStartFadein.PS_BattleStartFadein'"));

	if (PostProcessMat)
	{
		FWeightedBlendable Blendable;
		Blendable.Object = PostProcessMat;
		Blendable.Weight = 1.0f;

		Camera->PostProcessSettings.WeightedBlendables.Array.Add(Blendable);
		Camera->PostProcessBlendWeight = 1.0f;
	}
}
