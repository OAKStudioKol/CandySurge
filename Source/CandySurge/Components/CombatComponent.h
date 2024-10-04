// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AMasterWeapon;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CANDYSURGE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	void SpawnAndAttachWeapons();
	FVector GetTargetFromPlayerView() const;

	//Direct reference to the primary weapon actor
	UPROPERTY(BlueprintReadOnly,Category = "Weapons")
	AMasterWeapon* PrimaryWeapon;

	//Direct reference to the secondary weapon actor
	UPROPERTY(BlueprintReadOnly,Category = "Weapons")
	AMasterWeapon* SecondaryWeapon;
	
	//Direct reference to the secondary weapon actor
	UPROPERTY(BlueprintReadOnly,Category = "Weapons")
	AMasterWeapon* EquippedWeapon;

	UFUNCTION(BlueprintCallable)
	AMasterWeapon* CycleToNextWeapon();
	
	UFUNCTION(BlueprintCallable)
	AMasterWeapon* CycleToPreviousWeapon();

	//Equip a new weapon and hostler the current one if exists
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AMasterWeapon* Weapon);

	//puts the gun in hostler and sets the equipped weapon to null
	UFUNCTION(BlueprintCallable)
	void HolsterWeapon(AMasterWeapon* Weapon);

protected:
	virtual void BeginPlay() override;

private:

	int32 EquipSlot = 0;
	
	//Primary Weapon to spawn the character with 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMasterWeapon> PrimaryWeaponClass;

	//Secondary Weapon to spawn the character with 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMasterWeapon> SecondaryWeaponClass;
	
	//reference to the owner character (owner must derive from the ACharacter class)
	ACharacter* OwnerCharacter;
};
