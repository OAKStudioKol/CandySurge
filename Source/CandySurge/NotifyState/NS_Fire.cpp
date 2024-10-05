// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_Fire.h"

#include "CandySurge/Components/CombatComponent.h"
#include "CandySurge/Weapons/MasterWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UNS_Fire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	OwnerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp->GetWorld(), 0));

	CombatComp = Cast<UCombatComponent>(OwnerCharacter->GetComponentByClass(UCombatComponent::StaticClass()));

	if (OwnerCharacter)
	{

		if (OwnerCharacter->IsLocallyControlled())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("NOTIFY Fired"));
			CombatComp->EquippedWeapon->Fire(CombatComp->GetTargetFromPlayerView());
		}
	}
	
}
