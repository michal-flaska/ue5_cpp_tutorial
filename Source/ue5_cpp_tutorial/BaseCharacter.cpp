// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "PickupBase.h"

#include "Engine/OverlapResult.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 400.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BeginPlay called"));

	// if (APlayerController* PC = Cast<APlayerController>(GetController()))
	// {
	//	   GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Controller found"));
	// }

	// ----
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Default, 0);
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move,		ETriggerEvent::Triggered,	this, &ABaseCharacter::Move		);
		EnhancedInput->BindAction(IA_Look,		ETriggerEvent::Triggered,	this, &ABaseCharacter::Look		);
		EnhancedInput->BindAction(IA_Interact,	ETriggerEvent::Started,		this, &ABaseCharacter::Interact	); //changed triggered to started (i hope you know why)
	}
}

// move func
void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Input.Y);
	AddMovementInput(GetActorRightVector(), Input.X);
}

// look func
void ABaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

// interact func
void ABaseCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Pressed"));

	FVector Start = GetActorLocation(); // where the player is in the world

	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(200.f); // i try to imagine an invisible sphere around the player

	if (GetWorld()->OverlapMultiByChannel(Overlaps, Start, FQuat::Identity, ECC_WorldDynamic, Sphere))	// asks UE: "what actors are inside this sphere right now?"
																										// and fills the Overlaps array with everything it finds
	{
		for (FOverlapResult& Overlap : Overlaps) // loop through everything found
		{
			APickupBase* Pickup = Cast<APickupBase>(Overlap.GetActor()); // try to cast it to PickupBase — Cast returns null if it's not a PickupBase
			if (Pickup) // if cast succeeded(it IS a pickup)
			{
				Pickup->Destroy();	// self explanatory ig
				break;				// stop looking, we only want one
			}
		}
	}
}