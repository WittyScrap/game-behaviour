// Fill out your copyright notice in the Description page of Project Settings.
#include "SolarSystem.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

#include <stdint.h>
#include <math.h>

// Sets default values
ASolarSystem::ASolarSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

__forceinline uint8_t __fastcall Sign(float f)
{
	uint32_t x = *(uint32_t*)(void*)&f;
	return 1 & (x << (sizeof(uint32_t) * 8 - 1));
}

// Called every frame
void ASolarSystem::Tick(float DeltaTime)
{
	this->SetActorScale3D({ this->Scale, this->Scale, this->Scale });
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

	for (uint8_t i = 0; i < len; ++i)
	{
		position = FMath::VRand();
		position *= this->PlanetsConfiguration[i].Distance;

		APlanet* planet = Cast<APlanet>(world->SpawnActor(this->PlanetsConfiguration[i].Type, &position, &rotation, spawnParams));

		this->Planets[i] = planet;

		planet->Parent = this->Planets[0];
		planet->Sun = this->Planets[0];
		planet->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}