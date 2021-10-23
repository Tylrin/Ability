// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GameplayAbilitySystemComponent.h"

void UGameplayAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	if (AbilityActorInfo)
	{
		if (UGameInstance* GameInstance = InOwnerActor->GetGameInstance())
		{
			// Sign up for possess/unpossess events so that we can update the cached AbilityActorInfo accordingly
			GameInstance->GetOnPawnControllerChanged().AddDynamic(this, &UGameplayAbilitySystemComponent::OnPawnControllerChanged);
		}
	}

	GrantDefaultAbilitiesAndAttributes();
}

void UGameplayAbilitySystemComponent::BeginDestroy()
{
	if (AbilityActorInfo && AbilityActorInfo->OwnerActor.IsValid())
	{
		if (UGameInstance* GameInstance = AbilityActorInfo->OwnerActor->GetGameInstance())
		{
			GameInstance->GetOnPawnControllerChanged().RemoveAll(this);
		}
	}

	Super::BeginDestroy();
}

FGameplayAbilitySpecHandle UGameplayAbilitySystemComponent::GrantAbilityOfType(TSubclassOf<UGameplayAbility> AbilityType, bool bRemoveAfterActivation)
{
	FGameplayAbilitySpecHandle AbilityHandle;
	if (AbilityType)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityType);
		AbilitySpec.RemoveAfterActivation = bRemoveAfterActivation;

		AbilityHandle = GiveAbility(AbilitySpec);
	}
	return AbilityHandle;
}

void UGameplayAbilitySystemComponent::RemoveAbilityOfType(TSubclassOf<UGameplayAbility> AbilityType)
{
	FGameplayAbilitySpecHandle AbilityHandle;
	if (AbilityType)
	{
		ClearAbility(AbilityHandle);
	}
}

void ClearAbility(const FGameplayAbilitySpecHandle& Handle);

void UGameplayAbilitySystemComponent::GrantDefaultAbilitiesAndAttributes()
{
	// Reset/Remove abilities if we had already added them
	{
		//for (UAttributeSet* AttribSetInstance : AddedAttributes)
		//{
		//	GetSpawnedAttributes_Mutable().Remove(AttribSetInstance);
		//}

		for (FGameplayAbilitySpecHandle AbilityHandle : DefaultAbilityHandles)
		{
			SetRemoveAbilityOnEnd(AbilityHandle);
		}

		//AddedAttributes.Empty(DefaultAttributes.Num());
		DefaultAbilityHandles.Empty(DefaultAbilities.Num());
	}

	// Default abilities
	{
		DefaultAbilityHandles.Reserve(DefaultAbilities.Num());
		for (const TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
		{
			if (*Ability)
			{
				DefaultAbilityHandles.Add(GiveAbility(FGameplayAbilitySpec(Ability)));
			}
		}
	}

	// Default attributes
	//{
	//	for (const FGameplayAttributeApplication& Attributes : DefaultAttributes)
	//	{
	//		if (Attributes.AttributeSetType)
	//		{
	//			UAttributeSet* NewAttribSet = NewObject<UAttributeSet>(this, Attributes.AttributeSetType);
	//			if (Attributes.InitializationData)
	//			{
	//				NewAttribSet->InitFromMetaDataTable(Attributes.InitializationData);
	//			}
	//			AddedAttributes.Add(NewAttribSet);
	//			AddAttributeSetSubobject(NewAttribSet);
	//		}
	//	}
	//}
}

void UGameplayAbilitySystemComponent::OnPawnControllerChanged(APawn* Pawn, AController* NewController)
{
	if (AbilityActorInfo && AbilityActorInfo->OwnerActor == Pawn && AbilityActorInfo->PlayerController != NewController)
	{
		// Reinit the cached ability actor info (specifically the player controller)
		AbilityActorInfo->InitFromActor(AbilityActorInfo->OwnerActor.Get(), AbilityActorInfo->AvatarActor.Get(), this);
	}
}