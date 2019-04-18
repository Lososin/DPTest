// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

int AAI_Character::ActorsNum = 0;

// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(25.f, 96.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	GetMesh()->SetupAttachment(GetCapsuleComponent());
	GetMesh()->RelativeLocation = FVector(0.f, 0.f, -90.f);
	GetMesh()->RelativeRotation = FRotator(0, -90.f, 0);
	GetMesh()->bCastDynamicShadow = true;
	GetMesh()->CastShadow = true;

	// Create socket for a wearable Actor
	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	FName HandSocket = TEXT("HandSocket");
	HoldingComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), HandSocket);

	CurrentItem = nullptr;

	ActorsNum++;
	UniqID = ActorsNum;
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Character::PushObject()
{
	if (CurrentItem != nullptr)
	{
		CurrentItem->Push(1000, this->GetActorForwardVector());
		CurrentItem = nullptr;
	}
}

void AAI_Character::TakeAway()
{
	if (CurrentItem != nullptr)
	{
		PushObject();
	}
}

void AAI_Character::GrabObject(AActor* ActorToGrab)
{
	AWearableActor* WearableActor = Cast<AWearableActor>(ActorToGrab);

	if (WearableActor != nullptr)
	{
		if (WearableActor->IsGrabed() == false)
		{
			CurrentItem = WearableActor;
			bHoldingItem = true;
			CurrentItem->Pickup(HoldingComponent);
		}
	}
}

int AAI_Character::GetUniqID() const
{
	return UniqID;
}

void AAI_Character::RotateOnTheActor(AActor* TargetActor)
{
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), TargetActor->GetActorLocation());
	this->SetActorRotation(FRotator(this->GetActorRotation().Pitch, NewRotation.Yaw, this->GetActorRotation().Roll));
}

void AAI_Character::EnableCollision()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void AAI_Character::DisableCollision()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}