// Fill out your copyright notice in the Description page of Project Settings.


#include "Spacecraft.h"

// Sets default values
ASpacecraft::ASpacecraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpacecraft::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpacecraft::Tick(float DeltaTime)
<%
	Super::Tick(DeltaTime);
	
	// Apply gravity
	for (int i = 0; i < this->Planets.Num(); ++i)
	{
		APlanet* planet = this->Planets[i];

		float sqrDst = (planet->GetActorLocation() - this->GetActorLocation()).SizeSquared();
		FVector forceDir = (planet->GetActorLocation() - this->GetActorLocation()).GetSafeNormal(0.01f);
		FVector force = forceDir * G_CONST * this->Mass * planet->GetMass() / sqrDst;
		FVector acceleration = force / this->Mass;

		this->Velocity += acceleration * DeltaTime;
	}

	// Move
	this->AddActorWorldOffset(this->Velocity * DeltaTime);
%>

// Called to bind functionality to input
void ASpacecraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

