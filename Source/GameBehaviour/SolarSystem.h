// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Planet.h"
#include "EmptyNode.h"

#include "SolarSystem.generated.h"

USTRUCT(BlueprintType)
struct FPlanetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default") TSubclassOf<class APlanet> Type;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default") float Distance;
};

UCLASS()
class GAMEBEHAVIOUR_API ASolarSystem : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASolarSystem();

	// Input system
	virtual void SetupPlayerInputComponent(class UInputComponent* Input) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void MouseXAxis(float value);
	void MouseYAxis(float value);
	void ForwardAxis(float value);
	void HorizontalAxis(float value);
	void ZoomAxis(float value);

	void OnMouseDown();
	void OnMouseUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Solar System|Setup data")
	TArray<FPlanetData> 	PlanetsConfiguration;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Solar System|Runtime data (read-only)")
	TArray<APlanet*> 		Planets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar System|Setup data")
	float 					Scale = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar System|Setup data")
	float 					StillScale = 100.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar System|Setup data")
	FVector					Offset;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	UCameraComponent* 		PlayerCamera;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneComponent*		Root;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Solar System|Runtime data (read-only)")
	AEmptyNode*				SystemRoot;

private:
	FVector					MovementVector;
	FRotator				RotationRotator;

};
