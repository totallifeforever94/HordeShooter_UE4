// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SProjectileWeapon.generated.h"

UCLASS()
class SHOOTER_API ASProjectileWeapon : public ASWeapon
{
	GENERATED_BODY()

public:
	ASProjectileWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Fire() override;

	virtual AController *GetOwnerController() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Weapon")
	TSubclassOf<AActor> ProjectileClass;
};
