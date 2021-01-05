// Fill out your copyright notice in the Description page of Project Settings.


#include "Spacecraft.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASpacecraft::ASpacecraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	this->SetRootComponent(this->Collision);
	this->Collision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	this->Collision->SetSimulatePhysics(true);
}

/**
 * This is called every frame.
 * 
 */
void ASpacecraft::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (this->Parent && this->Collision->IsSimulatingPhysics())
	{
		FVector dirToPlanet;
		float dst2;
		float soi2;

		dirToPlanet = this->GetActorLocation() - this->Parent->GetActorLocation();
		dst2 = dirToPlanet.SizeSquared();
		soi2 = this->Parent->GetSphereOfInfluence();
		soi2 *= soi2;

		if (this->Parent->Parent != this->Parent && dst2 > soi2)
		{
			this->Parent = this->Parent->Parent;
		}
		
		for(int i = 0; this->Parent->Parent == this->Parent && i < this->SolarSystem.Num(); i += 1)
		{
			dirToPlanet = this->GetActorLocation() - this->SolarSystem[i]->GetActorLocation();
			dst2 = dirToPlanet.SizeSquared();
			soi2 = this->SolarSystem[i]->GetSphereOfInfluence();
			soi2 *= soi2;

			if (dst2 < soi2)
			{
				this->Parent = this->SolarSystem[i];
			}
		}
	}
}