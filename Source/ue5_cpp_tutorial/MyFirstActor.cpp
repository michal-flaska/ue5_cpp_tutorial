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

	// --- sphere ---
	// --- sphere root ---
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Sphere->InitSphereRadius(150.f);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere->SetMobility(EComponentMobility::Movable);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMyFirstActor::OnOverlapEnd);

	// --- mesh ---
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
	}

	// --- overlap bind ---
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMyFirstActor::OnOverlapBegin);
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

	StartLocation = GetActorLocation();
	StartScale = Mesh->GetRelativeScale3D();

	SetActorTickEnabled(bCanRotate == true); // if bCanRotate is true, it will enable actor tick

	// UE_LOG(LogTemp, Warning, TEXT("MyFirstActor BeginPlay"));
	UE_LOG(LogTemp, Warning, TEXT("World is %s"), *GetWorld()->GetName());

	if (BaseMaterial)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		Mesh->SetMaterial(0, DynamicMaterial);
	}

}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("MyFirstActor Ticking"));

	if (bCanRotate == true) {

		// old code
		//	FRotator NewRotation = Mesh->GetRelativeRotation();
		//	NewRotation.Yaw += RotationSpeed * DeltaTime;
		//	NewRotation.Roll += RotationSpeed * DeltaTime;
		//	Mesh->SetRelativeRotation(NewRotation);

		// using deltatime because we want i	t to rotate per second, not by frame
		// on 120 fps → insane spin
		// on 30 fps → slower spin
		// DeltaTime makes it per second.
		// engine fundamentals unlocked.
		// now run it and confirm cube spins.
		// then we upgrade it to rotate the mesh component only, not the whole actor.that will teach local vs world space.

		Mesh->AddLocalRotation(
			FRotator(0.f, RotationSpeed * DeltaTime, RotationSpeed * DeltaTime)
		);

		// ----

		float FloatTime = GetWorld()->GetTimeSeconds() * FloatSpeed;
		float ZOffset = FMath::Sin(FloatTime) * FloatAmplitude;

		FVector NewLocation = StartLocation;
		NewLocation.Z += ZOffset;

		SetActorLocation(NewLocation);

		// ----

		float ScaleTime = GetWorld()->GetTimeSeconds() * ScaleSpeed;
		float ScaleOffset = FMath::Sin(ScaleTime) * ScaleAmplitude;

		FVector NewScale = StartScale;
		NewScale += FVector(ScaleOffset);

		Mesh->SetRelativeScale3D(NewScale);
		

		// --- material ---
		if (OverlapMaterial)
		{
			Mesh->SetMaterial(0, OverlapMaterial);
		}
	}
}

void AMyFirstActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());

	if (OverlapMaterial)
	{
		Mesh->SetMaterial(0, OverlapMaterial);
	}
}

void AMyFirstActor::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (BaseMaterial)
	{
		Mesh->SetMaterial(0, BaseMaterial);
	}
}
