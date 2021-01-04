// Fill out your copyright notice in the Description page of Project Settings.


#include "Spacecraft.h"

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