// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Planet.h"

#include "Spacecraft.generated.h"

UCLASS()
class GAMEBEHAVIOUR_API ASpacecraft : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpacecraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/**
	 * Sets this body in orbit around the given parent body and sets
	 * itself as its child.
	 * 
	 * @param parent The body to orbit
	 */
	UFUNCTION(BlueprintCallable)
	void Orbit(APlanet* parent)
	{
		FVector direction = parent->GetActorLocation() - this->GetActorLocation();
		float velocity = FMath::Sqrt(G_CONST * parent->GetMass() / direction.Size());
		FVector orbit = FVector::CrossProduct(FVector::UpVector, direction.GetSafeNormal(0.01f));

		this->Velocity = orbit * velocity;
		this->Parent = parent;

		this->PreviousParentLocation = this->Parent->GetActorLocation();
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

private:
	FVector						PreviousParentLocation;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	FString 					CraftName = "Planet";
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Properties")
	float						Mass = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spacecraft|Physics")
	FVector 					Velocity = { 0, 0, 0 };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spacecraft|Physics")
	APlanet*					Parent;


};
