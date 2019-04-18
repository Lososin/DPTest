// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FPS_Character.h"
#include "AI_Character.h"
#include "AI_Enemy_Controller.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMICPIXELSTEST_API UMyBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()

public:
	UMyBTService_CheckForPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
