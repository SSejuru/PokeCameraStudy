// Fill out your copyright notice in the Description page of Project Settings.


#include "PokeDynamicCamera.h"

#include "PokePlayerController.h"
#include "Camera/CameraComponent.h"

// Sets default values
APokeDynamicCamera::APokeDynamicCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	RootComponent = CameraComp;

	CameraBlendTime = 0.5f;
}

// Called when the game starts or when spawned
void APokeDynamicCamera::BeginPlay()
{
	Super::BeginPlay();

	APokePlayerController* PC = Cast<APokePlayerController>(GetOwner());
	if(PC)
	{
		OwnerController = PC;
	}
}

// Called every frame
void APokeDynamicCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APokeDynamicCamera::BlendToCamera()
{
	OwnerController->SetViewTargetWithBlend(this, CameraBlendTime, BlendType.GetValue(), BlendExp);
}

