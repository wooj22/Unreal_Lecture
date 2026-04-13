// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetCurrentState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Zombie.h"

EBTNodeResult::Type UBTTask_SetCurrentState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Zombie)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(),
		(uint8)Zombie->CurrentState);

	return EBTNodeResult::Succeeded;
}
