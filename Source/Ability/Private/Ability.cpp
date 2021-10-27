// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ability.h"

#define LOCTEXT_NAMESPACE "FAbilityModule"

void FAbilityModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAbilityModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

DEFINE_LOG_CATEGORY(LogAbility);
	
IMPLEMENT_MODULE(FAbilityModule, Ability)