#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Character/GameplayAbilitySystemComponent.h"
#include "Character/Abilities/GASAbilityTypes.h"
#include "Character/Abilities/GASGameplayAbility.h"
#include "Character/Abilities/GASGameplayEffectTypes.h"
#include "GASBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UGASBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Returns the player's editor window role - Server (listen host) or Client #
	UFUNCTION(BlueprintCallable)
		static FString GetPlayerEditorWindowRole(UWorld* World);


	/**
	* GameplayAbility
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
		static UGameplayAbility* GetPrimaryAbilityInstanceFromHandle(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle);

	UFUNCTION(BlueprintCallable, Category = "Ability")
		static UGameplayAbility* GetPrimaryAbilityInstanceFromClass(UAbilitySystemComponent* AbilitySystemComponent, TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable, Category = "Ability")
		static bool IsPrimaryAbilityInstanceActive(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAbilitySpecHandle Handle);


	/**
	* FGameplayAbilitySpecHandle
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
		static bool IsAbilitySpecHandleValid(FGameplayAbilitySpecHandle Handle);


	/**
	* FGASGameplayEffectContainerSpec
	*/

	// USTRUCTs cannot contain UFUNCTIONS so we make static functions here
	// Checks if spec has any effects
	UFUNCTION(BlueprintPure, Category = "Ability|Container")
		static bool DoesEffectContainerSpecHaveEffects(const FGASGameplayEffectContainerSpec& ContainerSpec);

	// Checks if spec has any targets
	UFUNCTION(BlueprintPure, Category = "Ability|Container")
		static bool DoesEffectContainerSpecHaveTargets(const FGASGameplayEffectContainerSpec& ContainerSpec);

	// Clears spec's targets
	UFUNCTION(BlueprintCallable, Category = "Ability|Container")
		static void ClearEffectContainerSpecTargets(UPARAM(ref) FGASGameplayEffectContainerSpec& ContainerSpec);

	// Adds targets to a copy of the passed in effect container spec and returns it
	UFUNCTION(BlueprintCallable, Category = "Ability|Container", Meta = (AutoCreateRefTerm = "TargetData, HitResults, TargetActors"))
		static void AddTargetsToEffectContainerSpec(UPARAM(ref) FGASGameplayEffectContainerSpec& ContainerSpec, const TArray<FGameplayAbilityTargetDataHandle>& TargetData, const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);

	// Applies container spec that was made from an ability
	UFUNCTION(BlueprintCallable, Category = "Ability|Container")
		static TArray<FActiveGameplayEffectHandle> ApplyExternalEffectContainerSpec(const FGASGameplayEffectContainerSpec& ContainerSpec);


	/**
	* FGASGameplayEffectContext
	*/

	// Returns TargetData
	UFUNCTION(BlueprintCallable, Category = "Ability|EffectContext", Meta = (DisplayName = "GetTargetData"))
		static FGameplayAbilityTargetDataHandle EffectContextGetTargetData(FGameplayEffectContextHandle EffectContext);

	// Adds TargetData
	UFUNCTION(BlueprintCallable, Category = "Ability|EffectContext", Meta = (DisplayName = "AddTargetData"))
		static void EffectContextAddTargetData(FGameplayEffectContextHandle EffectContextHandle, const FGameplayAbilityTargetDataHandle& TargetData);


	/**
	* FGameplayAbilityTargetDataHandle
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability|TargetData")
		static void ClearTargetData(UPARAM(ref) FGameplayAbilityTargetDataHandle& TargetData);
};
