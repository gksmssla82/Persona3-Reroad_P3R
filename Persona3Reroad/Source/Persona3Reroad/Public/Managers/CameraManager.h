// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActionBase.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;
class ULevelSequence;
class ACineCameraBase;
class UMovieScene;
class ATBC_CharacterBase;

UCLASS()
class PERSONA3REROAD_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void InitializeSetCamerasRotation();
	void ToStartFromEndCamera(ATBC_CharacterBase* Target, FName StartKey, FName EndKey, float BlendTime) const;
	void ToAttachCameraFromSoket(ATBC_CharacterBase* Target, FName Key, FName SocketName) const;
	void CurrntCameraBlendTarget(ATBC_CharacterBase* Target, FName Key, float BlendTime) const;
	void PlayerSubAction(ATBC_CharacterBase* Target, FName EndKey, float BlendTime) const;
	void WorldCameraFromToCamera(FName StartKey, FName EndKey, float BlendTime) const;

public:
	UFUNCTION(BlueprintCallable)
	void Sequence_BattleStart() const;
	UFUNCTION(BlueprintCallable)
	void Sequence_SummonPersona(AActor* Player);
	UFUNCTION(BlueprintCallable)
	void Sequence_MainAllOut();
	UFUNCTION(BlueprintCallable)
	void Sequence_YukariAllOut();
	UFUNCTION(BlueprintCallable)
	void Sequence_MitsuruAllOut();
	UFUNCTION(BlueprintCallable)
	void SummonSequenceLoad();
	UFUNCTION(BlueprintCallable)
	void Sequence_MainVictory();
	UFUNCTION(BlueprintCallable)
	void Sequence_YukariVictory();
	UFUNCTION(BlueprintCallable)
	void Sequence_JunpaiVictory();
	UFUNCTION(BlueprintCallable)
	void Sequence_MituruVictory();



	

public:
	UPROPERTY(EditAnywhere, Category=Camera)
	TMap<FName, TObjectPtr<ACameraActionBase>> Cameras;

	UPROPERTY(EditAnywhere, Category=Camera)
	TMap<FName, TObjectPtr<ACineCameraBase>> CineCameras;

	UPROPERTY(EditAnywhere, Category=Sequnce)
	TMap<FName, TObjectPtr<ULevelSequence>> Sequences;

	UPROPERTY(EditAnywhere, Category=Tag)
	TMap<FName, FName> BindingTag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sequnce)
	TObjectPtr<ULevelSequencePlayer> CurrentSequencePlayer;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sequnce)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sequnce)
	ALevelSequenceActor* SummonSequenceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sequnce)
	TObjectPtr<ULevelSequence> SummonSequenceAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Sequnce)
	TObjectPtr<ULevelSequencePlayer> VictorySequencePlayer;

	UPROPERTY(EditAnywhere, Category = BlendTime)
	float EnemyAttackBlendTime = 3.0f;

;
	



};
