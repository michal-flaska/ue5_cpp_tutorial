// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

// Constructor
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // for now i'll set it to false

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

}
