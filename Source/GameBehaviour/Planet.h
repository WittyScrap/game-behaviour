// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define G_CONST 0.0000000000674

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "SymbolsCore.h"

#include "Planet.generated.h"

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
class GAMEBEHAVIOUR_API APlanet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Initializes data
	virtual void OnConstruction(const FTransform& transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Returns the mass of this planet given its radius and
	 * gravity.
	 * 
	 * @return This planet's mass.
	 */
	UFUNCTION(BlueprintPure)
	float GetMass()
	{
		float radius = this->Radius * __UnitsOfMeasure[(int)this->UnitOfMeasure];
		return (this->Gravity * radius * radius) / G_CONST;
	}

	/**
	 * Returns the radius of this planet in world units.
	 * 
	 * @return This planet's radius.
	 */
	UFUNCTION(BlueprintPure)
	float GetUnitsRadius()
	{
		return this->Radius * __UnitsOfMeasure[(int)this->UnitOfMeasure] * 100;
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
	template<typename T>
	static T GetScaledUnit(T value, EMeasurementUnit unit)
	{
		return value * __UnitsOfMeasure[(int)unit];
	}

	/**
	 * Sets this body in orbit around the given parent body and sets
	 * itself as its child.
	 * 
	 * @param parent The body to orbit
	 */
	UFUNCTION(BlueprintCallable)
	void Orbit(APlanet* parent)
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

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* 		Atmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* 		Planet;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneCaptureComponent2D*	PreviewCamera;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Shader data")
	UMaterialInstance* 			AtmosphereMaterial;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Shader data")
	UMaterialInstance* 			PlanetMaterial;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	float 						RotationSpeed = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	float 						PlanetScale = 0.9f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	float 						Radius = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	EMeasurementUnit			UnitOfMeasure = EMeasurementUnit::Metre;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	FString 					PlanetName = "Planet";

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	float 						Gravity = 9.807f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	bool 						bFixed = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Planet|Physics", meta = (EditCondition = "!bFixed"))
	FVector 					Velocity = { 0, 0, 0 };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics", meta = (EditCondition = "!bFixed"))
	APlanet*					Parent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	APlanet*					Sun;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* 	DynamicAtmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* 	DynamicPlanet;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UTextureRenderTarget2D* 	PreviewTarget;
};
