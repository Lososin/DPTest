// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "WearableActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "AI_Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "FPS_Character.generated.h"


class UInputComponent;

UCLASS(config=Game)
class DYNAMICPIXELSTEST_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	virtual void BeginPlay();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void GrabObject();

	void PushObject();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

	UPROPERTY(EditAnywhere)
	AWearableActor* CurrentItem;

	// Line tracing functions and variables
	FVector ReturnReachLineEnd(float distance);
	FVector ReturnReachLineStart();
	FHitResult GetPhysicsBodyInReach();

	UPROPERTY(EditAnywhere)
	float ReachDistance = 150.f;

	UPROPERTY(EditAnywhere)
	float PushForce = 1000000.f;

	UPROPERTY(EditAnywhere)
	bool isDrawDebugLine = false;

	bool bHoldingItem = false;
};
