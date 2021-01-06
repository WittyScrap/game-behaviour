// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetRenderingLibrary.h"
#include "Engine.h"
#include "Planet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SetRootComponent(this->Root);

	this->Atmosphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Atmosphere"));
	this->Atmosphere->SetupAttachment(this->Root);

	this->Planet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planet"));
	this->Planet->SetupAttachment(this->Atmosphere);
	
	this->PreviewCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Preview Camera"));
	this->PreviewCamera->SetupAttachment(this->Planet);
	this->PreviewCamera->SetRelativeLocation({ -400.f, 0, 0 });
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();

	float radius = this->Radius / 100;
	this->SetActorScale3D({ radius, radius, radius });

	UWorld* world = GetWorld();
	this->PreviewTarget = UKismetRenderingLibrary::CreateRenderTarget2D(world, 256, 256);
	this->PreviewCamera->TextureTarget = this->PreviewTarget;
	
	this->DynamicAtmosphere = UMaterialInstanceDynamic::Create(this->AtmosphereMaterial, this);
	this->DynamicPlanet = UMaterialInstanceDynamic::Create(this->PlanetMaterial, this); 

	this->Atmosphere->SetMaterial(0, this->DynamicAtmosphere);
	this->Planet->SetMaterial(0, this->DynamicPlanet);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->Sun)
	{
		FVector lightDir = this->Sun->GetActorLocation() - this->GetActorLocation();

		this->DynamicAtmosphere->SetVectorParameterValue("Light Direction", lightDir);
		this->DynamicPlanet->SetVectorParameterValue("Light Direction", lightDir);
	}

	FVector location = this->GetActorLocation();
	location += this->Velocity * DeltaTime;

	this->AddActorLocalRotation(FRotator(0, this->RotationSpeed * DeltaTime, 0), false, NULL, ETeleportType::None);
	this->SetActorLocation(location);
}

// Updates shader data 
void APlanet::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	this->Atmosphere->SetMaterial(0, this->AtmosphereMaterial);
	this->Planet->SetMaterial(0, this->PlanetMaterial);

	this->Planet->SetRelativeScale3D({ this->PlanetScale, this->PlanetScale, this->PlanetScale });
}