// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

	/*
	if (GEngine)
	{
		const FRotator Loc = GetActorRotation();

		const FString Name = GetName(); // https://forums.unrealengine.com/t/how-to-get-actor-id-name-in-c/295965/6
										// GetName() returns the ID (the name you get if you hover over the object in the Outliner).
										// use GetLabel() to get the Label that is displayed 
										// both will work on actors

		const FString Msg = FString::Printf(TEXT("rotation of %s is %s"),*Name, *Loc.ToString());

		GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::Yellow, Msg);
		// the key must always be different, otherwise it will replace the screendebug message of other actors that use the same key
		// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/UEngine/AddOnScreenDebugMessage
	}
	*/
}