// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "floatingActor_1.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Sets default values
AfloatingActor_1::AfloatingActor_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Static Mesh Component and Attach to Root
	FloatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FloatMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	//If Mesh Asset is Found, Attach to Root and Set Location to 0 in X,Y,Z
	if(MeshAsset.Succeeded())
		FloatMesh->SetStaticMesh(MeshAsset.Object);
		FloatMesh->SetRelativeLocation(FVector(0.0f, 0.0f,0.0f));
}

// Called when the game starts or when spawned
void AfloatingActor_1::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AfloatingActor_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Define Actor Location and Rotation Variables
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	//Define RunningTime
	float RunningTime = GetGameTimeSinceCreation();

	//Add Sin to DeltaHeight
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;

	//Add Rotation to Yaw * Rotation Speed
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	//Set Actor Location and Rotation 
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

