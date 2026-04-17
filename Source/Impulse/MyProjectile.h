// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyProjectile.generated.h"

UCLASS()
class IMPULSE_API AMyProjectile : public AActor
{
	GENERATED_BODY()

public:
	AMyProjectile();

	UPROPERTY(VisibleAnywhere) USphereComponent* CollisionSphere;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere) UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Damage = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSpanSeconds = 3.f;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
};
