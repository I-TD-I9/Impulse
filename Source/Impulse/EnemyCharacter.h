// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class IMPULSE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	// Set by the Round Manager each round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float MaxHealth = 50.f;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float DamageAmount = 10.f;

	// Called by the spawner to scale health each round
	UFUNCTION(BlueprintCallable) void SetHealth(float NewMax);

	virtual float TakeDamage(float DamageAmt, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void Die();
	ACharacter* PlayerCharacter;
};
