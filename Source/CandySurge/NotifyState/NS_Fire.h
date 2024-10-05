// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CandySurge/Components/CombatComponent.h"
#include "NS_Fire.generated.h"

/**
 * 
 */
UCLASS()
class CANDYSURGE_API UNS_Fire : public UAnimNotifyState
{
	GENERATED_BODY()


protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
private:
	ACharacter* OwnerCharacter;
	UCombatComponent* CombatComp;
};
