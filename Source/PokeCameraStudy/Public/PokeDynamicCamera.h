// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PokeActor/PokeActor.h"
#include "PokeDynamicCamera.generated.h"

class APokePlayerController;
class UCameraComponent;

UCLASS()
class POKECAMERASTUDY_API APokeDynamicCamera : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<APokePlayerController> OwnerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category=Camera)
	float CameraBlendTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category=Camera)
	float BlendExp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Camera)
	TEnumAsByte<EViewTargetBlendFunction> BlendType;

public:	
	// Sets default values for this actor's properties
	APokeDynamicCamera();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UCameraComponent> CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable = CameraFunctions)
	void FocusPokeActor(APokeActor* PokeActor);

	UFUNCTION(BlueprintCallable, Category = CameraFunctions)
	void BlendToCamera();

	float GetBlendTime() const { return CameraBlendTime; }
};
