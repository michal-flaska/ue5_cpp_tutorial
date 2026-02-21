// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"

#include "PickupBase.generated.h"

UCLASS()
class UE5_CPP_TUTORIAL_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "! Mike's PickupBase|Pickup")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "! Mike's PickupBase|Pickup")
	USphereComponent* InteractionSphere;

	UPROPERTY(EditDefaultsOnly, Category = "! Mike's PickupBase|Pickup")
	float InteractionRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "!Mike's PickupBase|Pickup")
	float RotationSpeed = 100.f;

	virtual void OnConstruction(const FTransform& Transform) override;
};
