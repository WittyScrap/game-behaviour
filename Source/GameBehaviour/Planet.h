// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "SymbolsCore.h"
#include "OrbitalBody.h"

#include "Planet.generated.h"

UCLASS()
class GAMEBEHAVIOUR_API APlanet : public AOrbitalBody
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
	virtual float GetMass() override
	{
		float radius = this->Radius * this->PlanetScale;
		return this->Gravity * (radius * radius) / G_CONST;
	}

	/**
	 * Returns the radius of this planet in world units.
	 * 
	 * @return This planet's radius.
	 */
	UFUNCTION(BlueprintPure)
	float GetUnitsRadius()
	{
		return this->Radius;
	}

	/**
	 * Returns the radius of this planet in world units.
	 * This value excludes the atmosphere's height.
	 * 
	 * @return This planet's radius.
	 */
	UFUNCTION(BlueprintPure)
	float GetUnitsPlanetRadius()
	{
		return this->Radius * this->PlanetScale;
	}

	/**
	 * Event fired when a rocket hits this planet.
	 * Slows down the planet's orbit.
	 * 
	 * @param velocity The magnitude of the rocket's velocity vector on impact.
	 */
	UFUNCTION(BlueprintCallable)
	void OnHit(float speed);

	/**
	 * Event fired when this planet gets too close to the sun.
	 * Destroys the planet after the indicated time.
	 * 
	 * @param burnTime The time it takes for the planet to burn.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	void Burn(float burnTime);

private:
	float						BurnTimer = 0;
	float						DestroyTimer = 0;

public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneComponent*			Root;

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
	FString 					PlanetName = "Planet";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Planet|Physics")
	float 						Gravity = 9.807f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* 	DynamicAtmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* 	DynamicPlanet;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UTextureRenderTarget2D* 	PreviewTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Planet|Graphics")
	AOrbitalBody*				Sun;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Planet|Properties", meta = (ClampMin = "0.001"))
	float 						Strength = 1000;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Properties")
	bool 						bBurned;

};
