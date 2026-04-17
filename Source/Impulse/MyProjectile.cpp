// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"
#include "Kismet/GameplayStatics.h"

AMyProjectile::AMyProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(15.f);
	CollisionSphere->SetCollisionProfileName(TEXT("Projectile"));
	CollisionSphere->OnComponentHit.AddDynamic(this, &AMyProjectile::OnHit);
	RootComponent = CollisionSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpanSeconds);
}

void AMyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(),
			this, UDamageType::StaticClass());
		Destroy();
	}
}

