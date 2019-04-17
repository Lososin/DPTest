// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "WearableActor.generated.h"

UCLASS()
class AWearableActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWearableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

	UFUNCTION()
	void Pickup(USceneComponent* OwnerComponent);

	UFUNCTION()
	void Push(float PushForce, FVector Direction);

	UFUNCTION()
	void UpdateState();

	bool bHolding = false;
	bool bGravity = true;
};
