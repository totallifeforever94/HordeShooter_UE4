// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeaponProjectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UDamageType;

UCLASS()
class SHOOTER_API ASWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASWeaponProjectile();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent *ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem *ExplosionEffect;

	void ApplyDamage();

	FTimerHandle TimerHandle;

	UPROPERTY()
	TSubclassOf<UDamageType> DamageClass;
};
