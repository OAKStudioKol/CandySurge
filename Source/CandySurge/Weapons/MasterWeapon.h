// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MasterWeapon.generated.h"

class UDA_WeaponData;

UCLASS()
class CANDYSURGE_API AMasterWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMasterWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void Fire(FVector Target);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	const UDA_WeaponData* WeaponData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;
	
protected:

	virtual void BeginPlay() override;

private:
	ACharacter* OwnerCharacter;

};
