// Fill out your copyright notice in the Description page of Project Settings.

#include "WearableActor.h"

// Sets default values
AWearableActor::AWearableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(TEXT("PhysicsWearableActor"));
}

// Called when the game starts or when spawned
void AWearableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWearableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && HoldingComponent)
	{
		SetActorLocationAndRotation(
			HoldingComponent->GetComponentLocation(), 
			HoldingComponent->GetComponentRotation()
		);
	}
}

void AWearableActor::UpdateState() {
	Mesh->SetEnableGravity(bGravity);
	Mesh->SetSimulatePhysics(bHolding ? false : true);
	Mesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
}

void AWearableActor::Pickup(USceneComponent* OwnerComponent)
{
	HoldingComponent = Cast<USceneComponent>(OwnerComponent);
	bHolding = true;
	bGravity = false;
	UpdateState();
}

void AWearableActor::Push(float PushForce, FVector Direction)
{
	bHolding = false;
	bGravity = true;
	UpdateState();
	HoldingComponent = nullptr;
	Mesh->AddForce(Direction * PushForce * Mesh->GetMass());
}