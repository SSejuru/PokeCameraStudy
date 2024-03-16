// Fill out your copyright notice in the Description page of Project Settings.


#include "PokeActor/PokeActor.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PokeCameraStudy/PokeCameraStudyGameMode.h"

// Sets default values
APokeActor::APokeActor()
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	CapsuleComp->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CapsuleComp;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh Comp");
	SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	BattleSequenceDelay = 1.25f;
	AlertWidgetOffsetHeight = 50.0f;
}

// Called when the game starts or when spawned
void APokeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APokeActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APokeActor::OnBeginOverlap);
}


void APokeActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		APokeCameraStudyCharacter* PokeCharacter = Cast<APokeCameraStudyCharacter>(OtherActor);
		if(PokeCharacter)
		{
			StartWildEncounter(PokeCharacter);
			CapsuleComp->SetGenerateOverlapEvents(false);
		}
	}
}


void APokeActor::StartWildEncounter(APokeCameraStudyCharacter* PokePlayer)
{
	APlayerController* PC = Cast<APlayerController>(PokePlayer->GetController());
	if(PC)
	{
		AlertWidget = CreateWidget<UPokeWorldUserWidget>(PC, AlertWidgetClass);
		if(AlertWidget)
		{
			AlertWidget->WorldOffset = FVector(0, 0, AlertWidgetOffsetHeight);
			AlertWidget->AttachedActor = this;
			AlertWidget->AddToViewport();
		}
	}

	FTimerHandle TimerHandle;
	FTimerDelegate BattleDelegate = FTimerDelegate::CreateUObject(this, &APokeActor::CallBattleSequence, PokePlayer);

	GetWorldTimerManager().SetTimer(TimerHandle, BattleDelegate, BattleSequenceDelay, false);
}

void APokeActor::CallBattleSequence(APokeCameraStudyCharacter* PokePlayer)
{
	APokePlayerController* PC = Cast<APokePlayerController>(PokePlayer->GetController());
	if(PC)
	{
		PC->StartPokeBattle(PokePlayer, this);
	}

	FacePlayerForBattle(PokePlayer);
}

void APokeActor::PlayTauntAnim()
{
	UAnimInstance* Anim = SkeletalMeshComp->GetAnimInstance();
	if(Anim)
	{
		Anim->Montage_Play(TauntAnimation, 0.9f);
	}
	
}



