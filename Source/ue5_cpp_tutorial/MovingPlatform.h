// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class UE5_CPP_TUTORIAL_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	TArray<FVector> LocalPoints;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.f;

	UPROPERTY(EditInstanceOnly)
	TArray<USceneComponent*> ControlPoints;

	UPROPERTY()
	TArray<FVector> WorldPoints;

	int32 CurrentPointIndex = 0;

	void MovePlatform(float DeltaTime);
};
