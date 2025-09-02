// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/TurnBased/TBC_CharacterBase.h"
#include "Character/TurnBased/Enemy/TBC_EnemyBase.h"
#include "Character/TurnBased/Player/TBC_PlayerBase.h"
#include "Managers/EffectManager.h"
#include "System/BattleInstanceSubsystem.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



float UStatusComponent::CalculateDamage(ATBC_CharacterBase* Attacker, ATBC_CharacterBase* Target)
{
	UStatusComponent* AttackerStatus = Cast<UStatusComponent>(Attacker->GetComponentByClass(UStatusComponent::StaticClass()));
	UStatusComponent* TargetStatus = Cast<UStatusComponent>(Target->GetComponentByClass(UStatusComponent::StaticClass()));
	
	if (!AttackerStatus || !TargetStatus)
	{
		UE_LOG(LogTemp, Error, TEXT("Calculater Damage Attack Or Target Is Null!"));
		return 0.f;
	}

	// Evasion(회피) Check 
	if (TargetStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Evasion")))
	{
		return 0.0f;
	}
	
	float Damage = FMath::RandRange(AttackerStatus->Status.MinDamage, AttackerStatus->Status.MaxDamage);
	
	// Melee Attack
	if (AttackerStatus->Status.ElementAttack == EElement::Slash || AttackerStatus->Status.ElementAttack == EElement::Blow ||
		AttackerStatus->Status.ElementAttack == EElement::Penetration)
	{
		Damage += AttackerStatus->Status.Power;
	}

	// Magic Attack
	else if (AttackerStatus->Status.ElementAttack == EElement::Dark || AttackerStatus->Status.ElementAttack == EElement::Electric ||
		AttackerStatus->Status.ElementAttack == EElement::Fire || AttackerStatus->Status.ElementAttack == EElement::Ice ||
		AttackerStatus->Status.ElementAttack == EElement::Light || AttackerStatus->Status.ElementAttack == EElement::Wind)
	{
		Damage += AttackerStatus->Status.Mana;
	}

	// Critical Damage
	if (AttackerStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.TakeCritical")))
	{
		Damage *= AttackerStatus->Status.CriticalDamage;
	}

	// Resist Damage
	if (TargetStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Resist")))
	{
		Damage *= 0.8f; // 20% 깎음
	}

	// 가드시 데미지는 받음 대신 다운 면역 (회피도 가능)
	if (TargetStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Guard")))
	{
		Damage /= 2.0f;
	}

	Damage -= TargetStatus->Status.Defence;

	return FMath::RoundToInt(Damage);
}

// 타겟
void UStatusComponent::LastStanceCheck()
{
	// 죽음애니메이션 재생중에도 위젯은 떠야하니 스턴애니메이션과 Vfx만 DeadCheck
	// 스턴과 크리티컬은 둘중 하나만 한번뜸
	
	if (bIsSturn)
	{
		
		if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
		{
			Owner->GetMesh()->GetAnimInstance()->StopAllMontages(0.2f);
			Owner->StatusComponent->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.Sturn"));
			Owner->StatusComponent->SturnVfx_On();
		}
		
		bIsSturn = false;
		
		// 약점 위젯 처리 //
		if(OnWeakDeleGate.IsBound())
		{
			OnWeakDeleGate.Broadcast();
		}
		/////////////////
	}

	if (Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.TakeCritical")))
	{
		// 크리티컬 위젯 처리 //
		if (OnCriticalDeleGate.IsBound())
		{
			OnCriticalDeleGate.Broadcast();
		}

		////////////////////
	}

	

	/////////////// 기존 델리게이트 쓸거면 여기 약점/위젯/StatusComponent에 Damage맴버변수로 들고 넣어주기 /////////////

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	
}


// 공격전 한번만 호출
void UStatusComponent::CalculateStance(ATBC_CharacterBase* Attacker, ATBC_CharacterBase* Target)
{
	UStatusComponent* AttackerStatus = Cast<UStatusComponent>(Attacker->GetComponentByClass(UStatusComponent::StaticClass()));
	UStatusComponent* TargetStatus = Cast<UStatusComponent>(Target->GetComponentByClass(UStatusComponent::StaticClass()));
	
	if (!AttackerStatus || !TargetStatus)
	{
		UE_LOG(LogTemp, Error, TEXT("CalculateStance Attack Or Target Is Null!"));
		return;
	}

	// 1.회피 ,2.약점, 3.크리티컬, 4.저항
	
	// 1. 회피
	if (!TargetStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")))
	{
		float RandEvasion = FMath::RandRange(0.f, 100.f);
		if (RandEvasion <= TargetStatus->Status.EvasionProbability)
		{
			Target->StatusComponent->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.Evasion"));
			UE_LOG(LogTemp, Error, TEXT("%s 가 %s 의 공격을 회피판정"), *Target->GetName(), *Attacker->GetName());
			return;
		}
	}


	// 2. 약점
	if (AttackerStatus->Status.ElementAttack == TargetStatus->Status.ElementWeak)
	{
		// 가드 상태가 아닐떄
		if (!TargetStatus->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("Stance.Guard")))
		{
			AttackerStatus->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.OneMore"));
			TargetStatus->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.Weak"));
			//TargetStatus->SturnVfx_On();
			TargetStatus->bIsSturn = true; // 스턴 애니메이션은 후처리를 위해 bool로처리 후에 Sturn == true이면 Weak,Sturn 태그추가
			UE_LOG(LogTemp, Error, TEXT("%s 가 %s 의 공격을 약점판정"), *Target->GetName(), *Attacker->GetName());
			return;
		}
	}

	// 3. 크리티컬
	float RandCritical = FMath::RandRange(0.f, 100.f);
	if (RandCritical <= AttackerStatus->Status.CriticalProbability)
	{
		Target->StatusComponent->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.TakeCritical"));
		UE_LOG(LogTemp, Error, TEXT("%s 가 %s 의 공격을 크리티컬판정"), *Target->GetName(), *Attacker->GetName());
	}

	// 4. 저항 (저항속성이여도 크리티컬은 뜸)
	if (TargetStatus->Status.ElementResist == AttackerStatus->Status.ElementAttack)
	{
		TargetStatus->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.Resist"));
		UE_LOG(LogTemp, Error, TEXT("%s 가 %s 의 공격을 저항판정"), *Target->GetName(), *Attacker->GetName());
	}
}

void UStatusComponent::TakeDamage(float Damage)
{

	// 죽지않고 회피이고 회피Once가 false면
	if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")) &&
	    !Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")) &&
		Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Evasion")) &&
		!bIsEvasionOnce)
	{
		if (UAnimMontage* AvoidMontage = Owner->Montages.FindRef("Avoid"))
		{
			UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();
			
			AnimInstance->Montage_Play(AvoidMontage);

			UE_LOG(LogTemp, Error, TEXT("%s 가 회피몽타주 실행"), *Owner->GetName());

			////////// 회피 위젯 처리 //////////
			if (OnMissDeleGate.IsBound())
			{
				OnMissDeleGate.Broadcast();
			}
			/////////////////////////////////
			
			
			bIsEvasionOnce = true;
		}
	}

	if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")) &&
		!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")) &&
		Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Resist")) &&
		!bIsResist)
	{

		if (OnResistDeleGate.IsBound())
		{
			OnResistDeleGate.Broadcast();
		}
		
		bIsResist = true;
	}

	
	
	// 죽지않고 회피가 아닐떄 데미지처리
	if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Evasion")) &&
		!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
	{
		Status.CurrentHp = FMath::Clamp(Status.CurrentHp - Damage, 0.f, Status.MaxHp);
	}
	
	//Widget Delegate //파티패널 쉐이크
	if (Damage > 0 && OnHitDeleGateNoParam.IsBound())
	{
		OnHitDeleGateNoParam.Broadcast();
	}

	//Floating Damage /데미지 표시
	if (Damage > 0 && OnHitDeleGateThreeParam.IsBound())
	{
		OnHitDeleGateThreeParam.Broadcast(Damage);
	}
	

	if (!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Sturn")) &&
		!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Evasion")) &&
		!Owner->StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.IsDead")))
	{
		if (UAnimMontage* DamageMontage = Owner->Montages.FindRef("Damage"))
		{
			UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance();
			
			AnimInstance->Montage_Play(DamageMontage);
		}
	}
	
	
	if (Status.CurrentHp <= 0.f)
	{
		if (Owner && Owner->GetMesh())
		{
			if (UAnimInstance* AnimInstance = Owner->GetMesh()->GetAnimInstance())
			{
				AnimInstance->StopAllMontages(0.2f);
			}
		}
		
		Owner->StatusComponent->Get_GameTag().AddTag(FGameplayTag::RequestGameplayTag("State.IsDead"));
		SturnVfx_Off();
		return;
	}
	
	UE_LOG(LogTemp, Error, TEXT("%s 가 %f 만큼 데미지 입음!"), *Owner->GetName(),Damage);
}

void UStatusComponent::ApplyDamage(float Damage)
{
	
	TakeDamage(Damage);
	
}

void UStatusComponent::RemoveTag(ATBC_CharacterBase* Target)
{
	UStatusComponent* StatusComponent = Target->StatusComponent;
	
		StatusComponent->bIsEvasionOnce = false;
	    StatusComponent->bIsResist = false;
	
		if (StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.TakeCritical")))
		{
			StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.TakeCritical"));
		}
	
		if (StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Weak")))
		{
			StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.Weak"));
		}
	
		if (StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Resist")))
		{
			StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.Resist"));
		}
	
		if (StatusComponent->Get_GameTag().HasTag(FGameplayTag::RequestGameplayTag("State.Evasion")))
		{
		    StatusComponent->Get_GameTag().RemoveTag(FGameplayTag::RequestGameplayTag("State.Evasion"));
		}

}

void UStatusComponent::DecreaseSp(float Sp)
{
	FMath::Clamp(Status.CurrentSp -= Sp, 0, Status.MaxSp);
}


void UStatusComponent::SturnVfx_On()
{

	// 기존 컴포넌트가 있다면 먼저 파괴 (새로 생성하기 위함)
	if (SturnNiagaraComponent && SturnNiagaraComponent->IsValidLowLevelFast())
	{
		SturnNiagaraComponent->DestroyComponent(); 
		SturnNiagaraComponent = nullptr; // 포인터 초기화
		UE_LOG(LogTemp, Warning, TEXT("Previous KnockDown Effect Destroyed."));
	}

	if (UBattleInstanceSubsystem* SubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UBattleInstanceSubsystem>())
	{
		UNiagaraSystem* KnockDownVfx = SubSystem->BattleEffectManager->Get_Effect("KnockDown");
		if (KnockDownVfx)
		{
			SturnNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		 KnockDownVfx,
		 Owner->GetMesh(),
		 FName("SturnVfx"),
		 FVector::ZeroVector,
		 FRotator::ZeroRotator,
		 EAttachLocation::SnapToTargetIncludingScale,
		 true,  
		 true    
	  );
			UE_LOG(LogTemp, Warning, TEXT("KnockDown Effect Newly Spawned."));
		}
	}
}


void UStatusComponent::SturnVfx_Off() 
{
	if (SturnNiagaraComponent && SturnNiagaraComponent->IsValidLowLevelFast())
	{
		SturnNiagaraComponent->DestroyComponent();
		SturnNiagaraComponent = nullptr; 
		UE_LOG(LogTemp, Warning, TEXT("KnockDown Effect Destroyed."));
	}
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ATBC_CharacterBase>(GetOwner());

	Status.CurrentHp = Status.MaxHp;
	Status.CurrentSp = Status.MaxSp;
}




