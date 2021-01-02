// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASWeapon::ASWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BaseDamage = 20.f;
	MuzzleSocketName = TEXT("MuzzleFlashSocket");
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASWeapon::Fire()
{
	AController *WeaponOwnerController = GetOwnerController();

	if (WeaponOwnerController)
	{
		FVector Location;
		FRotator Rotation;
		WeaponOwnerController->GetPlayerViewPoint(Location, Rotation);

		FVector ShotDirection = Rotation.Vector();

		FVector TraceEnd = Location + (ShotDirection * 10000);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		Params.AddIgnoredActor(this);
		Params.bTraceComplex = true;

		FVector TracerEndPoint = TraceEnd;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Location, TraceEnd, ECC_Visibility, Params))
		{
			AActor *HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, GetOwner()->GetInstigatorController(), this, DamageType);

			if (ImpactEffect != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			TracerEndPoint = Hit.ImpactPoint;
		}

		DrawDebugLine(GetWorld(), Location, TraceEnd, FColor::Red, false, 1.f, 0, 1.f);

		if (MuzzleFlash != nullptr)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComp, MuzzleSocketName);
		}

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent *TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeTrail, MuzzleLocation);

		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TEXT("BeamEnd"), TracerEndPoint);
		}
	}
}

AController *ASWeapon::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}

	AController *OwnerController = OwnerPawn->GetController();

	return OwnerController;
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
