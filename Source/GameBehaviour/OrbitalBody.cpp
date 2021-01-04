// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitalBody.h"
#include "DrawDebugHelpers.h"

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

// Called every frame
void AOrbitalBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->bPaused)
	{
		return;
	}
	
	DrawDebugLine(GetWorld(), this->GetActorLocation(), this->GetActorLocation() + this->Velocity, FColor(0, 0, 255, 255), false, 0, 1, 0);

	if (this->Parent && this->Parent != this)
	{
		// Apply gravity
		float sqrDst = (this->Parent->GetActorLocation() - this->GetActorLocation()).SizeSquared();
		FVector forceDir = (this->Parent->GetActorLocation() - this->GetActorLocation()).GetSafeNormal(0.01f);
		FVector acceleration = forceDir * G_CONST * this->Parent->GetMass() / sqrDst;

		DrawDebugLine(GetWorld(), this->GetActorLocation(), this->GetActorLocation() + acceleration, FColor(255, 0, 0, 255), false, 0, 2, 0);

		this->Velocity += acceleration * DeltaTime;
	}

	this->PhysicsMove(DeltaTime);
}