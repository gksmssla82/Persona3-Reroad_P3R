// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SkillManager.h"

#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Persona/PersonaBase.h"
#include "Skill/SkillBase.h"
#include "System/BattleInstanceSubsystem.h"

// Sets default values
ASkillManager::ASkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillManager::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>()->Register_SKillManager(this);
	
}

void ASkillManager::Add_Skill(FName SkillName, ATBC_CharacterBase* SkillTarget,  APersonaBase* PersonaSkill)
{
		
	if (const TSubclassOf<USkillBase>* Found = Skills.Find(SkillName))
	{
		if (*Found && (*Found)->IsValidLowLevelFast())
		{
			
			if (SkillTarget != nullptr)
			{
				USkillBase* SkillInstance = NewObject<USkillBase>(SkillTarget, *Found);
				SkillTarget->SkillList.AddUnique(SkillInstance);
			}

			if (PersonaSkill != nullptr)
			{
				USkillBase* SkillInstance = NewObject<USkillBase>(PersonaSkill, *Found);
				PersonaSkill->SkillList.AddUnique(SkillInstance);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Found Skill Class is invalid or null"));
		}
	}
	

}



