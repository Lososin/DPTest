// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WearableActor.generated.h"

UCLASS()
class AWearableActor : public AActor
{
	GENERATED_BODY()
/*
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* Sphere;
	*/
public:	
	// Sets default values for this actor's properties
	AWearableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
public:
	// Returns Mesh1P subobject
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return Mesh; }
	// Returns FirstPersonCameraComponent subobject 
	FORCEINLINE class USphereComponent* GetSphereCollision() const { return Sphere; }
	*/
};
