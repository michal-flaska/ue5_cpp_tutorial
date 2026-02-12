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

	WorldPoints.Empty(); // clear world points in case beginplay run again in PIE

	for (USceneComponent* Point : ControlPoints)
	{
		if (Point)
		{
			WorldPoints.Add(Point->GetComponentLocation());
		}
	}

	if (WorldPoints.Num() < 2) return;
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

