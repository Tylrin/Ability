// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GASGameplayAbility.h"
#include "AbilitySystemComponent.h"

UGASGameplayAbility::UGASGameplayAbility()
{
	bActivateAbilityOnGranted = false;
}

void UGASGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}