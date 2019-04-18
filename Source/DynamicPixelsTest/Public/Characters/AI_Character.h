// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "WearableActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_Character.generated.h"

UCLASS(config=game)
class DYNAMICPIXELSTEST_API AAI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* EnemyBehavior;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GrabObject(AActor* ActorToGrab);

	void PushObject();

	void TakeAway();

	void RotateOnTheActor(AActor* TargetActor);

	int GetUniqID() const;

	void EnableCollision();

	void DisableCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

	UPROPERTY(EditAnywhere)
	AWearableActor* CurrentItem;
	
	bool bHoldingItem = false;

	static int ActorsNum;

	int UniqID;
};
