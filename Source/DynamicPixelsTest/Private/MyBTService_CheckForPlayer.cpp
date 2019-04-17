// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_CheckForPlayer.h"

UMyBTService_CheckForPlayer::UMyBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UMyBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAI_Enemy_Controller* EnemyController = Cast<AAI_Enemy_Controller>(OwnerComp.GetAIOwner());

	if (EnemyController != nullptr)
	{
		AFPS_Character* Player = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Player != nullptr)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyController->PlayerID, Player);
		}
	}
}