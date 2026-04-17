// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "MyGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	// Cache the player reference once at spawn
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerCharacter) { return; }

	// Move directly toward the player every frame
	FVector Direction = (PlayerCharacter->GetActorLocation()
		- GetActorLocation()).GetSafeNormal();
	Direction.Z = 0.f;

	AddMovementInput(Direction, 1.f);
}

void AEnemyCharacter::SetHealth(float NewMax)
{
	MaxHealth = NewMax;
	CurrentHealth = NewMax;
}

float AEnemyCharacter::TakeDamage(float DamageAmt, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmt, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= DamageAmt;

	if (CurrentHealth <= 0.f)
	{
		Die();
	}

	return DamageAmt;
}

void AEnemyCharacter::Die()
{
	// Notify the Game Mode an enemy has died
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(
		UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->OnEnemyDied();
	}

	// Disable collision so nothing else interacts with the corpse
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	// Auto destroy after 2 seconds
	SetLifeSpan(2.f);
}

