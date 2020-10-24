// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Planet.generated.h"

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

private:

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* Atmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UStaticMeshComponent* Planet;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Shader data")
	UMaterialInstance* AtmosphereMaterial;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Shader data")
	UMaterialInstance* PlanetMaterial;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	float RotationSpeed = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	float PlanetScale = 1.9f;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Properties")
	FString PlanetName = "Planet";

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	float Gravity = 9.807f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	bool bFixed = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics", meta = (EditCondition = "!bFixed"))
	FVector Velocity = { 0, 100, 0 };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics", meta = (EditCondition = "!bFixed"))
	APlanet*	Parent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Planet|Physics")
	APlanet*	Sun;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* DynamicAtmosphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Planet|Graphics")
	UMaterialInstanceDynamic* DynamicPlanet;

};
