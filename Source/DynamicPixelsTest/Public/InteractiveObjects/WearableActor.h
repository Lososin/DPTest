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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Using for attach Actor to a Pawn
	UFUNCTION()
	void Pickup(USceneComponent* OwnerComponent);

	// Using for detach Actor from a Pawn
	UFUNCTION()
	void Push(float PushForce, FVector Direction);

	// Return bHolding
	UFUNCTION()
	bool IsGrabed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	bool bHolding = false;
	bool bGravity = true;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

	// Called every change of Actor state
	UFUNCTION()
	void UpdateState();
};
