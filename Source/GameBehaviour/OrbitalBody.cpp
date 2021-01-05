// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitalBody.h"

// Sets default values
AOrbitalBody::AOrbitalBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_DuringPhysics;
}

// Called when the game starts or when spawned
void AOrbitalBody::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * Calculates the sphere of influence (SOI)
 * of this body.
 * 
 */
float AOrbitalBody::GetSphereOfInfluence()
{
	if (this->Parent)
	{
		// Approximate length of the semi-major axis.
		// Since this will realistically only be used for planets, and all planets in the
		// game follow circular orbits, the semi-major axis matches the distance from the planet
		// to its parent (most likely the sun).
		float a = (this->GetActorLocation() - this->Parent->GetActorLocation()).Size();
		float m = this->GetMass();
		float M = this->Parent->GetMass();

		return a * FMath::Pow(m / M, 2.f / 5.f);
	}

	return 0;
}

// Called every frame
void AOrbitalBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->bPaused)
	{
		return;
	}

	if (this->Parent && this->Parent != this)
	{
		// Apply gravity
		float sqrDst = (this->Parent->GetActorLocation() - this->GetActorLocation()).SizeSquared();
		FVector forceDir = (this->Parent->GetActorLocation() - this->GetActorLocation()).GetSafeNormal(0.01f);
		FVector acceleration = forceDir * G_CONST * this->Parent->GetMass() / sqrDst;

		this->AddImpulse(acceleration * DeltaTime);
	}
}