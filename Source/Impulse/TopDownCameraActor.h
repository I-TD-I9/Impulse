// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownCameraActor.generated.h"

UCLASS()
class IMPULSE_API ATopDownCameraActor : public AActor
{
	GENERATED_BODY()

public:
	ATopDownCameraActor();

	UPROPERTY(VisibleAnywhere) USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere) UCameraComponent* Camera;

	// How quickly the camera catches up to the player (higher = faster)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float FollowSpeed = 3.f;

	// Height and angle of the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float ArmLength = 900.f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ACharacter* TargetCharacter;
};
