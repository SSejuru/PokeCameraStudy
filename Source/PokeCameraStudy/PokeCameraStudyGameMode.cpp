// Copyright Epic Games, Inc. All Rights Reserved.

#include "PokeCameraStudyGameMode.h"
#include "PokeCameraStudyCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

APokeCameraStudyGameMode::APokeCameraStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APokeCameraStudyGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass()));
}

void APokeCameraStudyGameMode::SpawnPlayerCharacter(APokePlayerController* PlayerController)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerController;
	
	APokeCameraStudyCharacter* Character = GetWorld()->SpawnActor<APokeCameraStudyCharacter>(PlayerCharacterClass, PlayerStart->GetTransform(), SpawnParams);
	if(Character)
	{
		PlayerController->SetPlayerCharacter(Character);
		PlayerController->Possess(Character);
	}
}
