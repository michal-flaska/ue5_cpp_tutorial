// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "MyFirstActor.generated.h" // should always be included last

UCLASS()
class UE5_CPP_TUTORIAL_API AMyFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Rotation") // editanywhere means i can edit it in editor
	float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Rotation")
	bool bCanRotate = true; // booleans start with b. its not necessary but its a goood practice in UE

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Floating")
	float FloatAmplitude = 50.f;

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Floating")
	float FloatSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Scale")
	float ScaleAmplitude = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Mike's First Actor|Scale")
	float ScaleSpeed = 1.f;

	// --- dynamic mat glow ---

	float CurrentGlow = 0.f;
	float TargetGlow = 0.f;

	UPROPERTY(EditAnywhere, Category="Mike's First Actor|Glow")
	float GlowInterpSpeed = 5.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UMaterialInterface* CachedBaseMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bGameStarted = false;

	UPROPERTY(VisibleAnywhere, /* BlueprintReadOnly, */ Category = "Mike's First Actor")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	FVector StartLocation;
	FVector StartScale;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
