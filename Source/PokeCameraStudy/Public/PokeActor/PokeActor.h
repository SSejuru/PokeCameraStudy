// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PokeWorldUserWidget.h"
#include "GameFramework/Actor.h"
#include "PokeCameraStudy/PokeCameraStudyCharacter.h"
#include "PokeActor.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class POKECAMERASTUDY_API APokeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APokeActor();

protected:

	UPROPERTY(EditDefaultsOnly, Category = UI)
	float AlertWidgetOffsetHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPokeWorldUserWidget> AlertWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = UI)
	TObjectPtr<UPokeWorldUserWidget> AlertWidget;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	TObjectPtr<UAnimMontage> TauntAnimation;

	UPROPERTY(EditDefaultsOnly, Category= Battle)
	float BattleSequenceDelay;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void CallBattleSequence(APokeCameraStudyCharacter* PokePlayer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FacePlayerForBattle(APokeCameraStudyCharacter* PokePlayer);

public:

	UFUNCTION(BlueprintCallable)
	void StartWildEncounter(APokeCameraStudyCharacter* PokePlayer);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void PlayTauntAnim();
};
