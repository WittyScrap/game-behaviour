// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorUtilities.generated.h"

/**
 * Contains helper functions for actor utilities.
 * 
 */
UCLASS()
class GAMEBEHAVIOUR_API UActorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	/**
	 * Adds a new component of a specific class to a specified actor
	 * at runtime.
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category="Actor Utilities")
	static UActorComponent* AddComponentByClass(AActor* target, TSubclassOf<UActorComponent> type);
};
