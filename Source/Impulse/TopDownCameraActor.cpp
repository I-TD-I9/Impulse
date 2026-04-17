// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCameraActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ATopDownCameraActor::ATopDownCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = ArmLength;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void ATopDownCameraActor::BeginPlay()
{
	Super::BeginPlay();

	// Find the player character automatically
	TargetCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Set this as the active camera
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetViewTargetWithBlend(this, 0.5f);
	}
}

void ATopDownCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetCharacter) { return; }

	FVector TargetLocation = TargetCharacter->GetActorLocation();
	FVector CurrentLocation = GetActorLocation();

	// Smoothly interpolate toward the player
	FVector SmoothedLocation = FMath::VInterpTo(
		CurrentLocation,
		TargetLocation,
		DeltaTime,
		FollowSpeed
	);

	SetActorLocation(SmoothedLocation);
}

