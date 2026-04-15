// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 900.f;
    SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    SpringArm->bDoCollisionTest = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    GetCharacterMovement()->MaxWalkSpeed = Stats.MoveSpeed;
    bUseControllerRotationYaw = false;
}

void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayerCharacter::Shoot);
}

void AMyPlayerCharacter::MoveForward(float Value)
{
    AddMovementInput(FVector::ForwardVector, Value);
}

void AMyPlayerCharacter::MoveRight(float Value)
{
    AddMovementInput(FVector::RightVector, Value);
}

void AMyPlayerCharacter::Shoot()
{
    // Later
}
