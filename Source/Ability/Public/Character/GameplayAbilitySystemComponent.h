// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilitySystemComponent.generated.h"

class UAbilityAnimNotify;
class UAnimSequenceBase;
//class UInteractionAbilityAttributeSet;
class UDataTable;
class APawn;
class AController;

USTRUCT()
struct FGameplayAttributeApplication
{
	GENERATED_BODY()

	// Ability set to grant
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UInteractionAbilityAttributeSet> AttributeSetType;

	// Data table reference to initialize the attributes with, if any (can be left unset)
	UPROPERTY(EditAnywhere)
	UDataTable* InitializationData = nullptr;
};

UCLASS(ClassGroup = AbilitySystem, meta = (BlueprintSpawnableComponent))
class ABILITY_API UGameplayAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = Ability)
		TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = Ability)
		TArray<FGameplayAttributeApplication> DefaultAttributes;

	//~ Begin UAbilitySystemComponent interface
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	//~ End UAbilitySystemComponent interface

	//~ Begin UObject interface
	virtual void BeginDestroy() override;
	//~ End UObject interface

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Abilities")
		FGameplayAbilitySpecHandle GrantAbilityOfType(TSubclassOf<UGameplayAbility> AbilityType, bool bRemoveAfterActivation);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Abilities")
		void RemoveAbilityOfType(TSubclassOf<UGameplayAbility> AbilityType);

	//UFUNCTION(BlueprintCallable, Category = "Gameplay|Abilities")
	//	FGameplayAbilitySpecHandle FindAbilityHandleFromClass(TSubclassOf<UGameplayAbility> InAbilityClass);

protected:
	void GrantDefaultAbilitiesAndAttributes();

	UFUNCTION() // UFunction to be able to bind with dynamic delegate
	void OnPawnControllerChanged(APawn* Pawn, AController* NewController);
	TArray<FGameplayAbilitySpecHandle> DefaultAbilityHandles;

	UPROPERTY(transient)
	TArray<UAttributeSet*> AddedAttributes;
};
