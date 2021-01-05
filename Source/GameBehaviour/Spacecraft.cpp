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
		FVector velocityDir = this->Velocity - this->Parent->Velocity;
		
		DrawDebugLine(
			GetWorld(),
			this->GetActorLocation(),
			this->GetActorLocation() + velocityDir,
			FColor(0, 0, 255, 255),
			false,
			0, 2, 0.01f
		);

		FVector dirToPlanet = this->Parent->GetActorLocation();
		
		DrawDebugLine(
			GetWorld(),
			this->GetActorLocation(),
			dirToPlanet,
			FColor(255, 0, 0, 255),
			false,
			0, 2, 0.01f
		);
	}
}