// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	FVector StartLocation = GetActorLocation();

	for (const FVector& Point : LocalPoints)
	{
		WorldPoints.Add(StartLocation + Point);
	}

	if (WorldPoints.Num() > 0)
	{
		SetActorLocation(WorldPoints[0]);
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (WorldPoints.Num() < 2) return;

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = WorldPoints[CurrentPointIndex];

	FVector NewLocation = FMath::VInterpConstantTo(
		CurrentLocation,
		TargetLocation,
		DeltaTime,
		MoveSpeed
	);

	SetActorLocation(NewLocation);

	if (FVector::Dist(CurrentLocation, TargetLocation) < 5.f)
	{
		CurrentPointIndex++;

		if (CurrentPointIndex >= WorldPoints.Num())
		{
			CurrentPointIndex = 0;
		}
	}
}

