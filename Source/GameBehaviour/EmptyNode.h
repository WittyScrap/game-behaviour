// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptyNode.generated.h"

UCLASS()
class GAMEBEHAVIOUR_API AEmptyNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptyNode();
	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneComponent* Root;
};
