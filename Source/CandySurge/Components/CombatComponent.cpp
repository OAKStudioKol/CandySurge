// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "CandySurge/DataAssets/DA_WeaponData.h"
#include "CandySurge/Weapons/MasterWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	OwnerCharacter = nullptr;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		OwnerCharacter = Cast<ACharacter>(GetOwner());
	}

	SpawnAndAttachWeapons();
}

void UCombatComponent::SpawnAndAttachWeapons()
{
	FActorSpawnParameters SpawnParams;
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);

	SpawnParams.Owner = GetOwner();

	//Spawn and attach the primary weapon
	PrimaryWeapon = GetWorld()->SpawnActor<AMasterWeapon>(PrimaryWeaponClass,SpawnParams);
	EquipWeapon(PrimaryWeapon);

	//Spawn and attach the secondary weapon
	SecondaryWeapon = GetWorld()->SpawnActor<AMasterWeapon>(SecondaryWeaponClass,SpawnParams);
	HolsterWeapon(SecondaryWeapon);
	
}

FVector UCombatComponent::GetTargetFromPlayerView() const
{
	if (!OwnerCharacter || !OwnerCharacter->GetController())
	{
		return FVector::ZeroVector;
	}

	// Get player view location and rotation
	FVector PlayerViewLoc;
	FRotator PlayerViewRot;
	OwnerCharacter->GetController()->GetPlayerViewPoint(PlayerViewLoc, PlayerViewRot);

	// Calculate the end point of the trace
	FVector End = PlayerViewLoc + PlayerViewRot.Vector() * 8000.0f;

	// Perform a line trace to determine where to shoot
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(OwnerCharacter);

	bool bHit = GetOwner()->GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewLoc, End, ECollisionChannel::ECC_Visibility, TraceParams);

	// Optionally draw debug line
	//DrawDebugLine(GetWorld(), PlayerViewLoc, End, FColor::Blue, false, 1.0f);

	// Return the impact point if there's a blocking hit, otherwise return the trace end
	return bHit ? HitResult.ImpactPoint : End;
}

AMasterWeapon* UCombatComponent::CycleToNextWeapon()
{
	EquipSlot++;
	EquipSlot = FMath::Clamp(EquipSlot,0,2);
	switch (EquipSlot)
	{
	case 0:
		// Equip Primary Weapon
		UE_LOG(LogTemp, Warning, TEXT("Primary Weapon Selected"));
		EquipWeapon(PrimaryWeapon);
		break;

	case 1:
		// Equip Secondary Weapon
		UE_LOG(LogTemp, Warning, TEXT("Secondary Weapon Selected"));
		EquipWeapon(SecondaryWeapon);
		break;

	case 2:
		// Removing all weapons
		UE_LOG(LogTemp, Warning, TEXT("Tertiary Weapon Selected"));
		HolsterWeapon(EquippedWeapon);
		break;

	default:
		// Handle the default case if none of the above matches
		UE_LOG(LogTemp, Warning, TEXT("Unknown Weapon Selected"));
		HolsterWeapon(EquippedWeapon);
		break;
	}

	return EquippedWeapon;
}

AMasterWeapon* UCombatComponent::CycleToPreviousWeapon()
{
	EquipSlot--;
	EquipSlot = FMath::Clamp(EquipSlot,0,2);
	switch (EquipSlot)
	{
	case 0:
		// Equip Primary Weapon
		UE_LOG(LogTemp, Warning, TEXT("Primary Weapon Selected"));
		EquipWeapon(PrimaryWeapon);
		break;

	case 1:
		// Equip Secondary Weapon
			UE_LOG(LogTemp, Warning, TEXT("Secondary Weapon Selected"));
		EquipWeapon(SecondaryWeapon);
		break;

	case 2:
		// Removing all weapons
			UE_LOG(LogTemp, Warning, TEXT("Tertiary Weapon Selected"));
		HolsterWeapon(EquippedWeapon);
		break;

	default:
		// Handle the default case if none of the above matches
			UE_LOG(LogTemp, Warning, TEXT("Unknown Weapon Selected"));
		HolsterWeapon(EquippedWeapon);
		break;
	}
	
	return EquippedWeapon;
}

void UCombatComponent::EquipWeapon(AMasterWeapon* Weapon)
{
	if (Weapon && Weapon != EquippedWeapon)
	{
		if (EquippedWeapon)
		{
			HolsterWeapon(EquippedWeapon);
		}
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachRules,Weapon->WeaponData->EquipAttachmentSocket);
		EquippedWeapon = Weapon;
	}
}

void UCombatComponent::HolsterWeapon(AMasterWeapon* Weapon)
{
	if (Weapon)
	{
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachRules,Weapon->WeaponData->HostlerAttachmentSocket);
		EquippedWeapon = nullptr;
	}
}
