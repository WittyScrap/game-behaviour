// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyNode.h"

// Sets default values
AEmptyNode::AEmptyNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SetRootComponent(this->Root);
}

