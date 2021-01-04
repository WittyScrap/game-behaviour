// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define G_CONST 0.0000000000674

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrbitalBody.generated.h"

UCLASS()
class GAMEBEHAVIOUR_API AOrbitalBody : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbitalBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * The mass of this object.
	 * 
	 */
	UFUNCTION(BlueprintPure)
	virtual float GetMass() {
		return 0;
	}
	
	/**
	 * Sets this body in orbit around the given parent body and sets
	 * itself as its child.
	 * 
	 * @param parent The body to orbit
	 */
	UFUNCTION(BlueprintCallable)
	void Orbit(AOrbitalBody* parent)
	{
		if (parent != this)
		{
			FVector direction = parent->GetActorLocation() - this->GetActorLocation();
			FVector orbit = FVector::CrossProduct(FVector::UpVector, direction.GetSafeNormal(0.01f)).GetSafeNormal(0.01f);
			float velocity = FMath::Sqrt(G_CONST * parent->GetMass() / direction.Size());

			this->Velocity = orbit * velocity + parent->Velocity;
		}

		this->Parent = parent;
	}

	/**
	 * Performs a physical movement by the velocity vector.
	 * 
	 */
	virtual void PhysicsMove(float DeltaTime) 
	{
		FVector location = this->GetActorLocation();
		location += this->Velocity * DeltaTime;

		this->SetActorLocation(location);
	}
	
	/**
	 * Pauses or resumes the simulation for this solar system.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetPaused(bool Paused) 
	{
		this->bPaused = Paused;
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orbital Body|Physics", meta = (EditCondition = "!bFixed"))
	FVector 		Velocity = { 0, 0, 0 };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Orbital Body|Physics")
	bool 			bFixed = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orbital Body|Physics", meta = (EditCondition = "!bFixed"))
	AOrbitalBody*	Parent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Orbital Body|Runtime data (read-only)")
	bool			bPaused = false;

};
