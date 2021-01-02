// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUtilities.h"

/**
 * Adds a new component to a specified actor with a specified spawn type.
 * 
 */
UActorComponent* UActorUtilities::AddComponentByClass(AActor* Target, TSubclassOf<UActorComponent> Type)
{
    UActorComponent* NewComp = NewObject<UActorComponent>(Target, Type);
    NewComp->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above     

    return NewComp;
}