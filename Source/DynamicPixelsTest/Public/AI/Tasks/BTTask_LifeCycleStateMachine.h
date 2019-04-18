// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI_Character.h"
#include "FPS_Character.h"
#include "WearableActor.h"
#include "AI_Enemy_Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_LifeCycleStateMachine.generated.h"

enum StateMachine
{
	GO_TO_PLAYER,
	GIVE_MCGUFFIN,
	AWAIT,
	GO_TO_MCGUFFIN,
	GRAB_MCGUFFIN
};


UCLASS()
class DYNAMICPIXELSTEST_API UBTTask_LifeCycleStateMachine : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	StateMachine CurrenState = StateMachine::GO_TO_MCGUFFIN;

	FVector CalculatePosition(int ID, float Radius);
};
