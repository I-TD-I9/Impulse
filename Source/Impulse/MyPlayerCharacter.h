// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxHealth = 100.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentHealth = 100.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float MoveSpeed = 600.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Damage = 25.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Stamina = 100.f;
};

UCLASS()
class IMPULSE_API AMyPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyPlayerCharacter();

    UPROPERTY(VisibleAnywhere) USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere) UCameraComponent* Camera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FPlayerStats Stats;

    UFUNCTION(BlueprintCallable) void Shoot();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
};