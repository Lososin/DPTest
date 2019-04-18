// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LifeCycleStateMachine.h"

EBTNodeResult::Type UBTTask_LifeCycleStateMachine::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Enemy_Controller* EnemyPC = Cast<AAI_Enemy_Controller>(OwnerComp.GetAIOwner());
	AAI_Character* Character = Cast<AAI_Character>(EnemyPC->GetPawn());

	AWearableActor* Mcguffin = Cast<AWearableActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->McguffinID));
	AFPS_Character* Player = Cast<AFPS_Character>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->PlayerID));

	if (Mcguffin != nullptr && Player != nullptr)
	{
		switch (CurrenState)
		{
		case StateMachine::GO_TO_PLAYER:
			if (EnemyPC->MoveToLocation(Player->GetActorLocation() + CalculatePosition(Character->GetUniqID(), 100), 15, false, true, true, true, 0, true) == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				CurrenState = StateMachine::GIVE_MCGUFFIN;
			}
			break;

		case StateMachine::GIVE_MCGUFFIN:
			Character->RotateOnTheActor(Player);
			Character->PushObject();
			CurrenState = StateMachine::AWAIT;
			break;

		case StateMachine::AWAIT:
			Character->RotateOnTheActor(Player);
			Character->PushObject();
			if (FVector::Distance(Player->GetActorLocation(), Mcguffin->GetActorLocation()) > 200.f)
			{
				CurrenState = StateMachine::GO_TO_MCGUFFIN;
			}
			if (FVector::Distance(Player->GetActorLocation(), Character->GetActorLocation()) > 200.f)
			{
				CurrenState = StateMachine::GO_TO_PLAYER;
			}
			break;

		case StateMachine::GO_TO_MCGUFFIN:
			if (EnemyPC->MoveToLocation(Mcguffin->GetActorLocation(), 50, true, true, true, true, 0, true) == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				CurrenState = StateMachine::GRAB_MCGUFFIN;
			}
			break;

		case StateMachine::GRAB_MCGUFFIN:
			Character->GrabObject(Mcguffin);
			CurrenState = StateMachine::GO_TO_PLAYER;
			break;

		default:
			break;
		}

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

FVector UBTTask_LifeCycleStateMachine::CalculatePosition(int ID, float Distance)
{
	FVector2D BaseVector(1.f * Distance, 0.f);

	// Hardcoded, bc i know EnemyNum == 10
	float AlphaAngle = 360.f / 10.f * ID;

	return FVector((BaseVector.X * cos(AlphaAngle) - BaseVector.Y * sin(AlphaAngle)), (BaseVector.X * sin(AlphaAngle) + BaseVector.Y * cos(AlphaAngle)), 0);
}