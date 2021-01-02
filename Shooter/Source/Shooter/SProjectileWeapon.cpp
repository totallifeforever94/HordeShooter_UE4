// Fill out your copyright notice in the Description page of Project Settings.

#include "SProjectileWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ASProjectileWeapon::ASProjectileWeapon()
{
}

void ASProjectileWeapon::Tick(float DeltaTime)
{
}

void ASProjectileWeapon::Fire()
{
    AController *OwnerController = GetOwnerController();

    if (OwnerController && ProjectileClass)
    {
        FVector Location;
        FRotator Rotation;

        OwnerController->GetPlayerViewPoint(Location, Rotation);

        FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, Rotation, Params);
    }
}

AController *ASProjectileWeapon::GetOwnerController() const
{
    return Super::GetOwnerController();
}
