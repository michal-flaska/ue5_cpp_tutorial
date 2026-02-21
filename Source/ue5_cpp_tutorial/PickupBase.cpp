// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	// InteractionSphere->SetSphereRadius(InteractionRadius); //this was moved to onconstruction func

}

void APickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	InteractionSphere->SetSphereRadius(InteractionRadius);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->AddLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}

