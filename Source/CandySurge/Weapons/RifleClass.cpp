// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleClass.h"

#include "CandySurge/DataAssets/DA_WeaponData.h"
#include "Kismet/GameplayStatics.h"

void ARifleClass::Fire(FVector Target)
{
	// Clamp the firing time within a specified range (0 to MaxFiringTime in this case)
	FiringTime = FMath::Clamp(FiringTime + 0.2f, 0.0f, MaxFiringTime);

	FVector TraceStart = WeaponMesh->GetSocketLocation(WeaponData->FiringSocketName);
	FVector TraceEnd = Target;

	if (WeaponData->RecoilCurve)
	{
		float RecoilValue = WeaponData->RecoilCurve->GetFloatValue(FiringTime);

		// Apply upward recoil
		FVector UpwardRecoil = FVector(0.0f, 0.0f, RecoilValue);

		// Randomly decide whether recoil will be to the left or right
		float LateralDirection = FMath::RandBool() ? 1.0f : -1.0f;

		// Apply lateral recoil, using half of the recoil value
		FVector LateralRecoil = FVector(0.0f, LateralDirection * RecoilValue * 0.5f, 0.0f);

		// Add the recoil offsets to the original target location
		TraceEnd = Target + UpwardRecoil + LateralRecoil;
	}

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	if (bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect, HitResult.Location, FRotator::ZeroRotator);
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect, Target, FRotator::ZeroRotator);
	}

	// Set bIsFiring to true to indicate that the weapon is firing
	bIsFiring = true;

	// Clear any existing timer to prevent multiple timers running concurrently
	GetWorld()->GetTimerManager().ClearTimer(RecoilRecoveryTimerHandle);

	// Start the recoil recovery timer to decrement FiringTime periodically
	GetWorld()->GetTimerManager().SetTimer(RecoilRecoveryTimerHandle, this, &ARifleClass::DecrementFiringTime, 0.1f, true);
}


void ARifleClass::DecrementFiringTime()
{
    // Decrement FiringTime for recoil recovery
    FiringTime = FMath::Clamp(FiringTime - 0.1f, 0.0f, MaxFiringTime);

    // Stop the timer if firing time is zero and set bIsFiring to false
    if (FiringTime <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(RecoilRecoveryTimerHandle);
        bIsFiring = false;
    }
}