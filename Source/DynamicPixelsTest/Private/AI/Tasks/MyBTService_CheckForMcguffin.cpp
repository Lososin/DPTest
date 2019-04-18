// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_CheckForMcguffin.h"

template<typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

UMyBTService_CheckForMcguffin::UMyBTService_CheckForMcguffin()
{
	bCreateNodeInstance = true;
}

void UMyBTService_CheckForMcguffin::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAI_Enemy_Controller* EnemyController = Cast<AAI_Enemy_Controller>(OwnerComp.GetAIOwner());

	if (EnemyController != nullptr)
	{
		TArray<AWearableActor*> AllWearableActors;
		FindAllActors(GetWorld(), AllWearableActors);

		if (AllWearableActors.Num() != 0)
		{
			AWearableActor* Mcguffin = AllWearableActors[0];

			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyController->McguffinID, Mcguffin);
		}
	}
}
