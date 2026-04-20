#include "BTTask_CheckDist.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ZombieAIController.h"


UBTTask_CheckDist::UBTTask_CheckDist()
{
	NodeName = TEXT("CheckDistance");
}

EBTNodeResult::Type UBTTask_CheckDist::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (Player)
	{
		AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
		AZombieAIController* ZombieAIC = Cast<AZombieAIController>(OwnerComp.GetAIOwner());

		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		float Distance = FVector::Dist2D(ZombieLocation, PlayerLocation);

		//switch (TargetCondition)
		//{
		//	case ECondition::GraterThan:
		//	{
		//		if (Distance > TargetDistance)
		//		{
		//			ZombieAIC->SetState(TargetState);
		//		}
		//
		//		break;
		//	}
		//	case ECondition::LessThan:
		//	{
		//		if (Distance > TargetDistance)
		//		{
		//			ZombieAIC->SetState(TargetState);
		//		}
		//		break;
		//	}
		//}
	}

	return EBTNodeResult::Succeeded;
}
