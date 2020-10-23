// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Atmosphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Atmosphere"));
	this->SetRootComponent(this->Atmosphere);

	this->Planet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planet"));
	this->Planet->SetupAttachment(this->Atmosphere);
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Updates shader data 
void APlanet::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	this->Atmosphere->SetMaterial(0, this->AtmosphereMaterial);
	this->Planet->SetMaterial(0, this->PlanetMaterial);

	this->Planet->SetRelativeScale3D({ this->PlanetScale, this->PlanetScale, this->PlanetScale });
}