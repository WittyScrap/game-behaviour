// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUtilities.h"

/**
 * Contains helper functions for actor utilities.
 * 
 */
UActorComponent* UActorUtilities::AddComponentByClass(AActor* target, TSubclassOf<UActorComponent> type) {
    UActorComponent* newcomp = NewObject<UActorComponent>(target, type);
    
    if (!newcomp) {
        return NULL;
    }

    newcomp->RegisterComponent();    
    return newcomp;
}