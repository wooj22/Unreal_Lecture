#include "BTService_GetDist.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ZombieAIController.h"

UBTService_GetDist::UBTService_GetDist()
{
	NodeName = TEXT("GetDistance");
}

void UBTService_GetDist::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
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
}
