// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbitalBody.h"
#include "Components/CapsuleComponent.h"
#include "Planet.h"

#include "Spacecraft.generated.h"

UCLASS()
class GAMEBEHAVIOUR_API ASpacecraft : public AOrbitalBody
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpacecraft();

public:
	/**
	 * Returns the mass of this spacecraft.
	 * 
	 */
	virtual float GetMass() override
	{
		return this->Mass;
	}

	/**
	 * Adds a force to this spacecraft scaled by the spacecraft's
	 * mass.
	 * 
	 * @param force The force to apply to the spacecraft
	 */
	UFUNCTION(BlueprintCallable)
	void AddForce(const FVector& force)
	{
		this->Velocity += force / this->Mass;
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
	 * Performs a physical movement by the velocity vector.
	 * 
	 */
	virtual void PhysicsMove(float DeltaTime) override
	{
		if (this->Parent)
		{
			this->Collision->SetMassOverrideInKg(" ", this->Mass, true);
			this->Collision->SetPhysicsLinearVelocity(this->Velocity + this->Parent->Velocity);
		}
	}

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	FString 			CraftName = "Planet";
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	float				Mass = 100.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UCapsuleComponent*	Collision;


};
