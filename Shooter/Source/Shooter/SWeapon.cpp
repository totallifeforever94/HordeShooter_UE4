// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BaseDamage = 20.f;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASWeapon::Fire()
{
	AActor *WeaponOwner = GetOwner();

	if (WeaponOwner)
	{
		FVector Location;
		FRotator Rotation;
		WeaponOwner->GetActorEyesViewPoint(Location, Rotation);

		FVector ShotDirection = Rotation.Vector();

		FVector TraceEnd = Location + (Rotation.Vector() * 10000);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(WeaponOwner);
		Params.AddIgnoredActor(this);
		Params.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Location, TraceEnd, ECC_Visibility, Params))
		{
			AActor * HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, WeaponOwner->GetInstigatorController(), this, DamageType);
		}

		DrawDebugLine(GetWorld(), Location, TraceEnd, FColor::Red, false, 1.f, 0, 10.f);
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
