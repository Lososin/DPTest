// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Enemy_Controller.h"


AAI_Enemy_Controller::AAI_Enemy_Controller()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AAI_Enemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAI_Character* Char = Cast<AAI_Character>(InPawn);

	if (Char != nullptr && Char->EnemyBehavior != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*Char->EnemyBehavior->BlackboardAsset);

		PlayerID = BlackboardComp->GetKeyID("Player");
		McguffinID = BlackboardComp->GetKeyID("Mcguffin");

		BehaviorComp->StartTree(*Char->EnemyBehavior);
	}
}
