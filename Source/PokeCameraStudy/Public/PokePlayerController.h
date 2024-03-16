// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "PokeActor/PokeActor.h"
#include "PokeCameraStudy/PokeCameraStudyCharacter.h"
#include "PokePlayerController.generated.h"

class APokeDynamicCamera;
class APokeBattlePawn;
class APokeCameraStudyCharacter;

/**
 * 
 */
UCLASS()
class POKECAMERASTUDY_API APokePlayerController : public APlayerController
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	bool bIsOnCameraSequence;

protected:

	UPROPERTY(BlueprintReadOnly, Category = Cameras)
	TObjectPtr<APokeDynamicCamera> DynamicCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Possessable Pawns")
	TObjectPtr<APokeBattlePawn> BattlePawn;

	UPROPERTY(BlueprintReadOnly, Category = "Possessable Pawns")
	TObjectPtr<APokeCameraStudyCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Cameras)
	TSubclassOf<APokeDynamicCamera> DynamicCameraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Possessable Pawns")
	TSubclassOf<APokeBattlePawn> BattlePawnClass;

	UPROPERTY(EditDefaultsOnly, Category = PokeBattle)
	float BattlePositionDelay;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = PokeBattle)
	void SetBattlePositions(APokeCameraStudyCharacter* PokeCharacter, APokeActor* PokeActor);

	UFUNCTION()
	void PossessBattlePawn();

public:

	void SetPlayerCharacter(APokeCameraStudyCharacter* PokeCharacter) { PlayerCharacter = PokeCharacter; }

	UFUNCTION(Category = PokeBattle)
	void StartPokeBattle(APokeCameraStudyCharacter* PokeCharacter, APokeActor* PokeActor);

	UFUNCTION(BlueprintCallable, Category = PlayerCharacter)
	FTransform GetCharacterCameraTransform() const { return PlayerCharacter->GetFollowCamera()->GetComponentTransform(); }

	UFUNCTION(BlueprintCallable, Category = PlayerCharacter)
	APokeDynamicCamera* GetDynamicCamera() const { return DynamicCamera; }

	UFUNCTION(BlueprintCallable)
	void SwitchToBattlePawn();
};
