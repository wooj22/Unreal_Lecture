// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSPlayer.h"
#include "Zombie.h"

AZombieAIController::AZombieAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 800.f;
	Sight->LoseSightRadius = 600.f;
	Sight->PeripheralVisionAngleDegrees = 45.f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}

	SetState(EZombieState::Idle);
	AZombie* Zombie = Cast<AZombie>(GetPawn());
	if (Zombie)
	{
		Zombie->SetMaxSpeed(300.f);
	}

	SetGenericTeamId(1);

	// Delegate
	Perception->OnTargetPerceptionUpdated.AddDynamic
	(
		this, &AZombieAIController::ProcessTargetUpdated
	);

	Perception->OnTargetPerceptionForgotten.AddDynamic
	(
		this, &AZombieAIController::ProcessTargetForgotten
	);
}

void AZombieAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AZombieAIController::ProcessTargetUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception : %s"), *Actor->GetName());

	// 矫具贸府
	if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>())
	{
		ATPSPlayer* Player = Cast<ATPSPlayer>(Actor);
		AZombie* Zombie = Cast<AZombie>(GetPawn());

		// 好阑锭
		if (Stimulus.WasSuccessfullySensed())
		{
			if (Player && Zombie)
			{
				if (Zombie->CurrentState == EZombieState::Death) return;

				Blackboard->SetValueAsObject(TEXT("Player"), Player);
				SetState(EZombieState::Chase);
				Zombie->SetMaxSpeed(400.f);
			}
		}
		// 给好阑锭
		else
		{
			if (Player && Zombie)
			{
				if (Zombie->CurrentState == EZombieState::Death) return;

				Blackboard->SetValueAsObject(TEXT("Player"), nullptr);
				SetState(EZombieState::Idle);
				Zombie->SetMaxSpeed(800.f);
			}
		}
	}

	// 佃扁 贸府
	if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
	{

	}
}

void AZombieAIController::ProcessTargetForgotten(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception : %s"), *Actor->GetName());
}


void AZombieAIController::SetState(EZombieState NewState)
{
	Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)NewState);

	AZombie* Zombie = Cast<AZombie>(GetPawn());
	if (Zombie)
	{
		Zombie->CurrentState = NewState;
	}
}
