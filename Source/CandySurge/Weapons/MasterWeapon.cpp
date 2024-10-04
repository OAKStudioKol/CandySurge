// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWeapon.h"


// Sets default values
AMasterWeapon::AMasterWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the Weapon Mesh Component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

