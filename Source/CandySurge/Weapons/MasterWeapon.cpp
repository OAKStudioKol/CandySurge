// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"

#include "CandySurge/DataAssets/DA_WeaponData.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMasterWeapon::AMasterWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the Weapon Mesh Component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}


void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}



void AMasterWeapon::Fire(FVector Target)
{
	FVector TraceStart = WeaponMesh->GetSocketLocation(WeaponData->FiringSocketName);

	FHitResult HitResult;

	bool bHit =  GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,Target,ECC_Visibility);

	//DrawDebugLine(GetWorld(), TraceStart, Target, FColor::Blue, false, 5.0f, 0, 2.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Shot Fired"));

	if (bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect, HitResult.Location, FRotator::ZeroRotator);
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponData->HitParticleEffect,Target, FRotator::ZeroRotator);
	}
	
}
