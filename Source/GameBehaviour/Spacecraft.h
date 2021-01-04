// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbitalBody.h"
#include "Components/CapsuleComponent.h"
#include "Planet.h"

#include "Spacecraft.generated.h"

// Something's fishy with the mass here
UCLASS()
class GAMEBEHAVIOUR_API ASpacecraft : public AOrbitalBody
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpacecraft();

public:
	/**
	 * Adds a force to this spacecraft scaled by the spacecraft's
	 * mass.
	 * 
	 * @param force The force to apply to the spacecraft
	 */
	UFUNCTION(BlueprintCallable)
	void AddForce(const FVector& force)
	{
		this->Collision->AddForce(force, " ", false);
	}

	/**
	 * Sets whether or not the throttle is being manipulated.
	 * 
	 * @param throttling Whether or not the throttle is changing.
	 */
	UFUNCTION(BlueprintCallable)
	void SetThrottleDirection(float throttling)
	{
		this->OnThrottleDirectionSet(throttling);
	}

	/**
	 * Feeds roll, pitch, and yaw input values.
	 * 
	 * @param input The combined input values.
	 */
	UFUNCTION(BlueprintCallable)
	void SetInput(FRotator input)
	{
		this->OnInputSet(input);
	}

	/**
	 * Sets whether or not the throttle is being manipulated.
	 * 
	 * @param throttling Whether or not the throttle is changing.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnThrottleDirectionSet(float throttling);
	
	/**
	 * Sets whether or not the throttle is being manipulated.
	 * 
	 * @param throttling Whether or not the throttle is changing.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnInputSet(FRotator throttling);

	/**
	 * Pauses or resumes the simulation for this solar system.
	 * 
	 */
	virtual void SetPaused(bool Paused) override
	{
		Super::SetPaused(Paused);
		this->Collision->SetSimulatePhysics(!Paused);
	}

	/**
	 * Adds an impulse to this orbital body.
	 * Impulses ignore mass.
	 * 
	 */
	virtual void AddImpulse(FVector impulse) override
	{
		this->Velocity += impulse;
		this->Collision->AddImpulse(impulse, " ", true);
	}

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	FString 					CraftName = "Planet";
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	float						Mass = 100.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UCapsuleComponent*			Collision;


};
