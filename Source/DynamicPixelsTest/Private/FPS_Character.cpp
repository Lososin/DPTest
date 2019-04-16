// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Character.h"


// Sets default values
AFPS_Character::AFPS_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	GetMesh()->SetupAttachment(GetCapsuleComponent());
	GetMesh()->RelativeLocation = FVector(0.f, 0.f, -90.f);
	GetMesh()->RelativeRotation = FRotator(0, -90.f, 0);
	GetMesh()->bCastDynamicShadow = true;
	GetMesh()->CastShadow = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.f, 10.f, 0.f); // Position the camera
	FirstPersonCameraComponent->RelativeRotation = FRotator(0, 90.f, 0);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Attach camera to the Head Socket
	FName FPVCameraSocket = TEXT("FPVCamera");
	FirstPersonCameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), FPVCameraSocket);

	//
	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	FName HandSocket = TEXT("HandSocket");
	HoldingComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), HandSocket);

	CurrentItem = nullptr;
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (this->isDrawDebugLine)
	{
		DrawDebugLine(GetWorld(), ReturnReachLineStart(), ReturnReachLineEnd(ReachDistance), FColor::Green, false, 1, 0, 1);
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AFPS_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPS_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPS_Character::LookUpAtRate);

	// Bind Grab and Push events
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AFPS_Character::GrabObject);
	PlayerInputComponent->BindAction("Push", IE_Pressed, this, &AFPS_Character::PushObject);
}

//////////////////////////////////////////////////////////////////////////
// Events

void AFPS_Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPS_Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPS_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPS_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPS_Character::GrabObject()
{
	auto Hit = GetPhysicsBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();
	auto ActorHit = Hit.GetActor();

	AWearableActor* WearableActor = Cast<AWearableActor>(ActorHit);

	if (ActorHit) 
	{
		if (WearableActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("It is not a wearable Actor"));
		}
		else
		{
			if (CurrentItem != nullptr)
			{
				CurrentItem->Push(1000);
			}

			CurrentItem = WearableActor;
			bHoldingItem = true;
			CurrentItem->Pickup();
		}
	}
}

void AFPS_Character::PushObject()
{
	if (CurrentItem != nullptr)
	{
		CurrentItem->Push(PushForce);
		CurrentItem = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
// Line trace functions

FVector AFPS_Character::ReturnReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector AFPS_Character::ReturnReachLineEnd(float distance)
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * distance;
}

FHitResult AFPS_Character::GetPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResulst;
	GetWorld()->LineTraceSingleByObjectType(
		HitResulst,
		ReturnReachLineStart(),
		ReturnReachLineEnd(ReachDistance),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// Just for debug start
	AActor* ActorHit = HitResulst.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	// Just for debug end

	return HitResulst;
}