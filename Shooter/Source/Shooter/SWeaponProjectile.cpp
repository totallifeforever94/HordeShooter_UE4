// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeaponProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASWeaponProjectile::ASWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ExplosionEffect = CreateDefaultSubobject<UParticleSystem>("ExplosionEffect");

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 2000.f;
	ProjectileMovementComp->MaxSpeed = 2000.f;
	ProjectileMovementComp->bShouldBounce = true;
	ProjectileMovementComp->bRotationFollowsVelocity = true;

	InitialLifeSpan = 1.f;
}

// Called when the game starts or when spawned
void ASWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASWeaponProjectile::ApplyDamage, 1.f);
}

void ASWeaponProjectile::ApplyDamage()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation());
	TArray<AActor*> IgnoreActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.f, GetActorLocation(), 250.f, DamageClass, IgnoreActors, this, GetInstigatorController());

	DrawDebugSphere(GetWorld(), GetActorLocation(), 250.f, 12, FColor::Red, false, 1.f, 0, 3.f);

	Destroy();
}

// Called every frame
void ASWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
