// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorUtilities.generated.h"

/**
 * 
 */
UCLASS()
class GAMEBEHAVIOUR_API UActorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	/**
	 * Adds a new component to a specified actor with a specified spawn type.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	static UActorComponent* AddComponentByClass(AActor* Target, TSubclassOf<UActorComponent> Type);
};
