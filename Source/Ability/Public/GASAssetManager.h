// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UGASAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	static UGASAssetManager& Get();

	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;
};
