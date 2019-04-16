// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "WearableActor.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//FVector ReturnReachLineEnd();
	//FVector ReturnReachLineStart();
	//FHitResult GetPhysicsBodyInReach();

	//UPROPERTY(EditAnywhere)
	//float Reach = 100.f;

	//UFUNCTION(BlueprintCallable)
	//void Grab();

	//UFUNCTION(BlueprintCallable)
	//void Release();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
};
