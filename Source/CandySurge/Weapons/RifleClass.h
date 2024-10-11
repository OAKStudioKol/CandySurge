// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterWeapon.h"
#include "RifleClass.generated.h"

/**
 * 
 */
UCLASS()
class CANDYSURGE_API ARifleClass : public AMasterWeapon
{
	GENERATED_BODY()

public:
	void DecrementFiringTime();
	virtual void Fire(FVector Target) override;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFiring;

private:
	float FiringTime = 0;
	FTimerHandle RecoilRecoveryTimerHandle;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	double MaxFiringTime = 2;

};
