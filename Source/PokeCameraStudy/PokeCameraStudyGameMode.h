// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PokeCameraStudyCharacter.h"
#include "PokePlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "PokeCameraStudyGameMode.generated.h"

class APlayerStart;

UCLASS(minimalapi)
class APokeCameraStudyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APokeCameraStudyGameMode();

protected:

	UPROPERTY(BlueprintReadOnly, Category = Player)
	TObjectPtr<APlayerStart> PlayerStart;

	UPROPERTY(EditDefaultsOnly, Category = Player)
	TSubclassOf<APokeCameraStudyCharacter> PlayerCharacterClass;

	virtual void BeginPlay() override;

public:

	void SpawnPlayerCharacter(APokePlayerController* PlayerController);
};



