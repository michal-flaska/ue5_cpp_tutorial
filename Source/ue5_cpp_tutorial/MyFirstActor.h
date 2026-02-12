// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstActor.generated.h"

UCLASS()
class UE5_CPP_TUTORIAL_API AMyFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere) // editanywhere means i can edit it in editor
	float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	bool bCanRotate = true; // booleans start with b. its not necessary but its a goood practice in UE

	UPROPERTY(EditAnywhere, Category = "Floating")
	float FloatAmplitude = 50.f;

	UPROPERTY(EditAnywhere, Category = "Floating")
	float FloatSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Floating")
	float ScaleAmplitude = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Floating")
	float ScaleSpeed = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, /* BlueprintReadOnly, */ Category = "Components")
	UStaticMeshComponent* Mesh;

	FVector StartLocation;
	FVector StartScale;
};
