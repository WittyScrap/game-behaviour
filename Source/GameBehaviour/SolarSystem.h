// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Planet.h"
#include "EmptyNode.h"
#include "SymbolsCore.h"

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
	
	void MouseXAxis(float value);
	void MouseYAxis(float value);
	// void ForwardAxis(float value);
	// void HorizontalAxis(float value);
	// void ZoomAxis(float value);

	/**
	 * Focuses the camera on a specific planet (by-ID). 
	 * Planets IDs are assigned based on their entry index
	 * in the configuration array. 
	 * 
	 * All celestial bodies controlled by this `ASolarSystem` have
	 * an ID, including stars and moons. 
	 * 
	 * @param planetID The ID of the planet/celestial body to focus to
	 */
	__FORCE_INLINE__ void __FAST_CALL__ Focus(uint8_t planetID)
	{
		this->SystemRoot->SetActorLocation(-this->Planets[planetID]->GetActorLocation());
		this->PlayerCamera->SetRelativeLocation(-this->PlayerCamera->GetRelativeLocation().GetSafeNormal(0.01f) * this->Planets[planetID]->GetActorRelativeScale3D().X * this->Size);
	}

	/**
	 * Pauses the simulation for this solar system.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	void Pause() 
	{
		int len = this->Planets.Num();
		for (int i = 0; i < len; i += 1) 
		{
			this->Planets[i]->Pause();
		}
	}

	/**
	 * Resumes the simulation for this solar system.
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	void Unpause()
	{
		int len = this->Planets.Num();
		for (int i = 0; i < len; i += 1) 
		{
			this->Planets[i]->Unpause();
		}
	}


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
	float 					MovementSpeed = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar System|Setup data")
	float 					Size = 100.f;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	UCameraComponent*		PlayerCamera;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneComponent*		Root;
	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Components)
	USceneComponent*		Pivot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Solar System|Runtime data (read-only)")
	AEmptyNode*				SystemRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Solar System|Setup data", meta = (ClampMin = 0, SliderMin = 0))
	int						FocusedBody = 0;

};
