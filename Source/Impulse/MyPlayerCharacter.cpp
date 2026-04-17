// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyProjectile.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 900.f;
    SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    SpringArm->bDoCollisionTest = false;
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;
    SpringArm->SetAbsolute(false, true, false);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false;

    GetCharacterMovement()->MaxWalkSpeed = Stats.MoveSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    bUseControllerRotationYaw = false;
}

void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->bEnableClickEvents = true;

        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
        EIC->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Shoot);
    }
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) { return; }

    FHitResult HitResult;
    bool bHit = PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
    if (!bHit) { return; }

    FVector TargetLocation = HitResult.Location;
    FVector StartLocation = GetActorLocation();
    TargetLocation.Z = StartLocation.Z;

    if (FVector::Dist(TargetLocation, StartLocation) < 20.f) { return; }

    FVector Direction = (TargetLocation - StartLocation).GetSafeNormal();
    if (Direction.IsNearlyZero()) { return; }

    // Only rotate the actor yaw — camera is locked via SetAbsolute
    float TargetYaw = FMath::Atan2(Direction.Y, Direction.X) * (180.f / PI);
    SetActorRotation(FRotator(0.f, TargetYaw, 0.f));

    // Keep the spring arm's world rotation locked to our fixed top-down angle
    SpringArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));
}

void AMyPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (!Controller) { return; }

    const FRotator CameraRotation = FRotator(0.f,
        SpringArm->GetComponentRotation().Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void AMyPlayerCharacter::Shoot()
{
    if (!ProjectileClass) { return; }

    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 60.f;
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    GetWorld()->SpawnActor<AMyProjectile>(ProjectileClass, SpawnLocation,
        SpawnRotation, SpawnParams);
}
