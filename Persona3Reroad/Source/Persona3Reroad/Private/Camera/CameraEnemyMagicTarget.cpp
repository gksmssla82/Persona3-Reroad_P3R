// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraEnemyMagicTarget.h"

#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Components/TurnComponent.h"
#include "System/BattleInstanceSubsystem.h"


UCameraEnemyMagicTarget::UCameraEnemyMagicTarget()
{
}

void UCameraEnemyMagicTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp || !MeshComp->GetWorld())
	{
		return;
	}
	
	/////////////////////////////////////////// EFFECT ////////////////////////////////////////////////////////
	if (ATBC_CharacterBase* Owner = Cast<ATBC_CharacterBase>(MeshComp->GetOwner()))
	{
		if (UTurnComponent* Component = Owner->TurnComponent)
		{
			if (Component->Get_Target())
			{
				if (auto* Subsystem = MeshComp->GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
				{

					if (USkillBase* Skill = Owner->CurrentSkill)
					{
						if (Skill->GetSkillInfo().SkillTargetType == ETargetType::SingleTarget)
						{
							Subsystem->BattleCameraManager->PlayerSubAction(Owner->TurnComponent->Get_Target(),"PlayerSubCamera",2.0f);
						}
						else if (Skill->GetSkillInfo().SkillTargetType == ETargetType::AllTarget)
						{
							Subsystem->BattleCameraManager->WorldCameraFromToCamera("SkyStart","SkyEnd",8.0f);
						}
					}
				}
			}
			////////////////////////////////////////// Effect End ///////////////////////////////////////////////
		}
	}

	



	


	
	

}
