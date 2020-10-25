// Fill out your copyright notice in the Description page of Project Settings.


#include "GMSpace.h"
#include "SolarSystem.h"

// Initializes and sets default pawn
AGMSpace::AGMSpace(const FObjectInitializer& initializer)
{
    this->DefaultPawnClass = ASolarSystem::StaticClass();
}