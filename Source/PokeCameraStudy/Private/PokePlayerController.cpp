// Fill out your copyright notice in the Description page of Project Settings.


#include "PokePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "PokeBattlePawn.h"
#include "PokeDynamicCamera.h"
#include "Kismet/GameplayStatics.h"
#include "PokeCameraStudy/PokeCameraStudyGameMode.h"

void APokePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Spawn Player, BattlePawn and Dynamic Camera
	APokeCameraStudyGameMode* GM = Cast<APokeCameraStudyGameMode>(UGameplayStatics::GetGameMode(this));
	if(GM)
	{
		GM->SpawnPlayerCharacter(this);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (ensureAlways(DynamicCameraClass) && ensureAlways(BattlePawnClass))
	{
		DynamicCamera = GetWorld()->SpawnActor<APokeDynamicCamera>(DynamicCameraClass, PlayerCharacter->GetTransform(), SpawnParams);
		BattlePawn = GetWorld()->SpawnActor<APokeBattlePawn>(BattlePawnClass, PlayerCharacter->GetTransform(), SpawnParams);

		FRotator BattleRotator = FRotator(0, -45, 0);
		FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		BattlePawn->AttachToActor(PlayerCharacter, Rules);
		BattlePawn->SetActorRelativeRotation(BattleRotator);
	}

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}



void APokePlayerController::StartPokeBattle(APokeCameraStudyCharacter* PokeCharacter, APokeActor* PokeActor)
{
	if (bIsOnCameraSequence) return;

	bIsOnCameraSequence = true;
	DynamicCamera->FocusPokeActor(PokeActor);

	FTimerHandle TimerHandle;
	FTimerDelegate BattleDelegate = FTimerDelegate::CreateUObject(this, &APokePlayerController::SetBattlePositions, PokeCharacter, PokeActor);

	GetWorldTimerManager().SetTimer(TimerHandle, BattleDelegate, DynamicCamera->GetBlendTime() + BattlePositionDelay, false);
}

void APokePlayerController::SwitchToBattlePawn()
{
	SetViewTargetWithBlend(BattlePawn, 1, VTBlend_Cubic);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APokePlayerController::PossessBattlePawn, 1.1f);
}


void APokePlayerController::PossessBattlePawn()
{
	Possess(BattlePawn);
	EnableInput(this);
}
