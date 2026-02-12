// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

// Constructor
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // set to true because we are rotating the cube

	UE_LOG(LogTemp, Warning, TEXT("MyFirstActor Constructor"));
	
	/*
	UE_LOG(LogTemp, Warning, TEXT("World is %s"), *GetWorld()->GetName()); // will crash because constructor != gameplay context

	when editor loads a map :
		- engine allocates actor memory
		- constructor runs
		- components get created
		- world gets assigned
		- beginplay happens when game starts
		- constructor happens before the actor belongs to a world.

		thats why GetWorld was null and my game crashed
	*/

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); // my attempt to make the cpp actor movable in scene
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
	}


}

void AMyFirstActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("OnConstruction"));

	/*
	actor has phases:
	- C++ constructor
	- OnConstruction <- current function
	- PostInitializeComponents
	- BeginPlay
	- Tick
	*/
}

// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("MyFirstActor BeginPlay"));
	UE_LOG(LogTemp, Warning, TEXT("World is %s"), *GetWorld()->GetName());

}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("MyFirstActor Ticking"));

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 90.f * DeltaTime;	// deltatime because we want it to rotate per second, not by frame
											// on 120 fps ? insane spin
											// on 30 fps ? slower spin
											// DeltaTime makes it per second.
											// engine fundamentals unlocked.
											// now run it and confirm cube spins.
											// then we upgrade it to rotate the mesh component only, not the whole actor.that will teach local vs world space.
	SetActorRotation(NewRotation);


}
