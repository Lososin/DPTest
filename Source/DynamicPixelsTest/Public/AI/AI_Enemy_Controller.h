// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI_Character.h"
#include "AI_Enemy_Controller.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMICPIXELSTEST_API AAI_Enemy_Controller : public AAIController
{
	GENERATED_BODY()

public:
	AAI_Enemy_Controller();

	virtual void OnPossess(APawn* InPawn) override;

	uint8 PlayerID;
	uint8 McguffinID;

private:
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorComp;

	static int ActorCounts;

	int MyUniqID = 0;
};
