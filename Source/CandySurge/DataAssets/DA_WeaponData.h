// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_WeaponData.generated.h"


// Declaring the enum with UENUM()
UENUM(BlueprintType) // The "BlueprintType" specifier makes it usable in Blueprints
enum class EWeaponType : uint8
{
	Rifle   UMETA(DisplayName = "Rifle"),
	Pistol UMETA(DisplayName = "Pistol"),
	Unarmed UMETA(DisplayName = "Unarmed")
};


UCLASS()
class CANDYSURGE_API UDA_WeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName EquipAttachmentSocket;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName HostlerAttachmentSocket;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	EWeaponType WeaponType;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
    float FireRate;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UParticleSystem* HitParticleEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsAutomatic;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName FiringSocketName;
	
};
