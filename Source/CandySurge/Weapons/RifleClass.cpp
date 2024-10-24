// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleClass.h"


void ARifleClass::Fire(FVector Target)
{
    Super::Fire(Target);
}

void ARifleClass::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
void ARifleClass::Fire(FVector Target)
{
    if (!RecoilRecoveryTimerHandle.IsValid())
    {
        // Start the recoil recovery timer to decrement FiringTime periodically
        GetWorld()->GetTimerManager().SetTimer(RecoilRecoveryTimerHandle, this, &ARifleClass::DecrementFiringTime, 0.5f, true);
    }

    // Clamp the firing time within a specified range (0 to MaxFiringTime in this case)
    FiringTime = FMath::Clamp(FiringTime + 0.2f, 0.0f, MaxFiringTime);

    // Trace start is the socket location of the weapon
    FVector TraceStart = WeaponMesh->GetSocketLocation(WeaponData->FiringSocketName);
    
    // Calculate direction from weapon to target
    FVector Direction = (Target - TraceStart).GetSafeNormal();

    // Get the player's orientation (right and up vectors)
    FVector RightVector = WeaponMesh->GetRightVector();   // Right direction (lateral recoil)
    FVector UpVector = WeaponMesh->GetUpVector();         // Upward direction (vertical recoil)

    if (WeaponData->RecoilCurve)
    {
        // Get the recoil value from the curve based on firing time
        float RecoilValue = WeaponData->RecoilCurve->GetFloatValue(FiringTime);

        // Apply upward recoil
        FVector UpwardRecoil = UpVector * RecoilValue;

        // Randomly decide whether recoil will be to the left or right
        float LateralDirection = FMath::RandBool() ? 1.0f : -1.0f;

        // Apply lateral recoil, using half of the recoil value
        FVector LateralRecoil = RightVector * LateralDirection * RecoilValue * 0.5f;

        // Adjust the direction with the recoil (recoil is applied in local space)
        Direction = Direction + UpwardRecoil;

        // Normalize the direction again after applying recoil
        Direction = Direction.GetSafeNormal();

        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Recoil Added %f"), RecoilValue));
    }

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Firing time is %f"), FiringTime));

    // Now use the modified direction to calculate the new TraceEnd
    FVector TraceEnd = TraceStart + Direction * 10000.0f; // Adjust the trace length as needed

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);
    
    // Draw debug line to visualize the shot
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 1);

    // Handle hit or miss
    if (bHit)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect, HitResult.Location, FRotator::ZeroRotator);
    }
    else
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect, TraceEnd, FRotator::ZeroRotator); // Use TraceEnd if no hit
    }

    // Set bIsFiring to true to indicate that the weapon is firing
    bIsFiring = true;
}

void ARifleClass::DecrementFiringTime()
{
    // Decrement FiringTime for recoil recovery
    FiringTime = FMath::Clamp(FiringTime - 0.5f, 0.0f, MaxFiringTime);

    // Stop the timer if firing time is zero and set bIsFiring to false
    if (FiringTime <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(RecoilRecoveryTimerHandle);
        bIsFiring = false;
    }
}
*/
