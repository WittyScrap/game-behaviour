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
{
	Super::Tick(DeltaTime);
	
	FVector parentLocation = this->Parent->GetActorLocation();
	FVector offset = parentLocation - this->PreviousParentLocation;
	this->PreviousParentLocation = parentLocation;

	UE_LOG(LogTemp, Warning, TEXT("Offset: %s"), *offset.ToString());

	this->AddActorWorldOffset(offset);
	
	// Apply gravity
	float sqrDst = (this->Parent->GetActorLocation() - this->GetActorLocation()).SizeSquared();
	FVector forceDir = (this->Parent->GetActorLocation() - this->GetActorLocation()).GetSafeNormal(0.01f);
	FVector force = forceDir * G_CONST * this->Mass * this->Parent->GetMass() / sqrDst;
	FVector acceleration = force / this->Mass;

	this->Velocity += acceleration;

	// Move
	FVector location = this->GetActorLocation();
	location += this->Velocity;

	this->SetActorLocation(location);
}

// Called to bind functionality to input
void ASpacecraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

