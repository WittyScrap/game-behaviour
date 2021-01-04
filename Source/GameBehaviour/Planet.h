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
		float radius = this->Radius;
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

};
