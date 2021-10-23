// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAssetManager.h"
#include "AbilitySystemGlobals.h"

UGASAssetManager& UGASAssetManager::Get()
{
	UGASAssetManager* Singleton = Cast<UGASAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be GDAssetManager!"));
		return *NewObject<UGASAssetManager>();	 // never calls this
	}
}


void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}