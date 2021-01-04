// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define G_CONST 0.0000000000674

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrbitalBody.generated.h"

constexpr float __UnitsOfMeasure[8] = 
{
	0.00001,
	0.0001,
	0.001,
	0.01,
	0.1,
	1,
	1000,
	1000000
};

UENUM(BlueprintType)
enum class EMeasurementUnit : uint8
{
	Centimetre				UMETA(DisplayName = "Centimetre (cm)"),
	Decimetre				UMETA(DisplayName = "Decimetre (dm)"),
	Metre					UMETA(DisplayName = "Metre (m)"),
	Dekametre				UMETA(DisplayName = "Dekametre (dam)"),
	Hectometre				UMETA(DisplayName = "Hectometre (hm)"),
	Kilometre				UMETA(DisplayName = "Kilometre (km)"),
	Megametre				UMETA(DisplayName = "Megametre (Mm)"),
	Gigametre				UMETA(DisplayName = "Gigametre (Gm)")
};

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
			float velocity = FMath::Sqrt(G_CONST * parent->GetMass() / direction.Size());
			FVector orbit = FVector::CrossProduct(FVector::UpVector, direction.GetSafeNormal(0.01f));

			this->Velocity = orbit * velocity;
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
		location += (this->Velocity + this->Parent->Velocity) * DeltaTime;

		this->SetActorLocation(location);
	}
	
	/**
	 * Pauses or resumes the simulation for this solar system.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	void SetPaused(bool Paused) 
	{
		this->bPaused = Paused;
	}

	/**
	 * Returns the multiplier value for a given measurement unit.
	 * 
	 * @param unit The measurement unit to retrieve a measure multiplier for.
	 * @return A multiplier for the given measure. For example, Metres will return 100.
	 */
	UFUNCTION(BlueprintPure)
	static float GetUnitOfMeasurement(EMeasurementUnit unit)
	{
		return __UnitsOfMeasure[(int)unit];
	}

	/**
	 * Returns the multiplier value for a given measurement unit.
	 * 
	 * @param unit The measurement unit to retrieve a measure multiplier for.
	 * @return A multiplier for the given measure. For example, Metres will return 100.
	 */
	UFUNCTION(BlueprintPure)
	static float GetScaledUnit(float value, EMeasurementUnit unit)
	{
		return value * __UnitsOfMeasure[(int)unit];
	}

	/**
	 * Scales a value by this body's selected unit.
	 * 
	 */
	float ScaledValue(float value)
	{
		return value * __UnitsOfMeasure[(int)this->UnitOfMeasure];
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orbital Body|Physics", meta = (EditCondition = "!bFixed"))
	FVector 			Velocity = { 0, 0, 0 };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Orbital Body|Physics")
	bool 				bFixed = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orbital Body|Physics", meta = (EditCondition = "!bFixed"))
	AOrbitalBody*		Parent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Orbital Body|Runtime data (read-only)")
	bool				bPaused = false;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Orbital Body|Properties")
	EMeasurementUnit	UnitOfMeasure = EMeasurementUnit::Metre;

};
