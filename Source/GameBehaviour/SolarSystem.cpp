// Fill out your copyright notice in the Description page of Project Settings.
#include "SolarSystem.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "FastMath.h"

#include <stdint.h>
#include <algorithm>
#include <math.h>

// Sets default values
ASolarSystem::ASolarSystem()
{
	PrimaryActorTick.bCanEverTick = false;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SetRootComponent(this->Root);

	this->Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	this->Pivot->SetupAttachment(this->Root);

	this->PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	this->PlayerCamera->SetupAttachment(this->Pivot);
}

// Manages input
void ASolarSystem::SetupPlayerInputComponent(class UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);

	// Bind all actions
	Input->BindAction("Select", IE_Pressed, this, &ASolarSystem::OnMouseDown);
	Input->BindAction("Select", IE_Released, this, &ASolarSystem::OnMouseUp);

	// Bind all axis
	Input->BindAxis("X Axis", this, &ASolarSystem::MouseXAxis);
	Input->BindAxis("Y Axis", this, &ASolarSystem::MouseYAxis);
// 	Input->BindAxis("Zoom", this, &ASolarSystem::ZoomAxis);
// 	Input->BindAxis("Horizontal", this, &ASolarSystem::HorizontalAxis);
// 	Input->BindAxis("Forward", this, &ASolarSystem::ForwardAxis);
}

// X axis handler
void ASolarSystem::MouseXAxis(float value)
{
	this->Pivot->AddLocalRotation({ 0, value * 2 * PI, 0 }, false, NULL);
}

// Y axis handler
void ASolarSystem::MouseYAxis(float value)
{
	; // NOOP
}

// Left mouse has been pressed
void ASolarSystem::OnMouseDown()
{
	; // NOOP
}

// Left mouse has been released
void ASolarSystem::OnMouseUp()
{
	; // NOOP
}

// Called when the game starts or when spawned
void ASolarSystem::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();
	int len = this->PlanetsConfiguration.Num();
	this->Planets.Init(NULL, len);

	FVector position;
	FRotator rotation;
		
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	spawnParams.Owner = this;

	this->SystemRoot = Cast<AEmptyNode>(world->SpawnActor(AEmptyNode::StaticClass(), &position, &rotation, spawnParams));
	this->SystemRoot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	for (uint8_t i = 0; i < len; ++i)
	{
		// Generate a random 2D vector
		float angle = FMath::RandRange(0.f, PI * 2.f);

		position.X = FMath::Cos(angle);
		position.Y = FMath::Sin(angle);

		// Place in correct distance
		position *= this->PlanetsConfiguration[i].Distance;

		APlanet* planet = Cast<APlanet>(world->SpawnActor(this->PlanetsConfiguration[i].Type, &position, &rotation, spawnParams));

		this->Planets[i] = planet;

		planet->Parent = this->Planets[0];
		planet->Sun = this->Planets[0];
		planet->AttachToActor(this->SystemRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
	
	this->SetActorScale3D({ this->Size, this->Size, this->Size });
	this->Focus(this->FocusedBody);
}