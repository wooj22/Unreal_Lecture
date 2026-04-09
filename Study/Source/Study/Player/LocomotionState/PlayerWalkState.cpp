// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWalkState.h"
#include "../MainState/PlayerLocomotionState.h"
#include "../PlayerMovementComponent.h"

void UPlayerWalkState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Walk"));
}

void UPlayerWalkState::OnUpdate(float DeltaTime)
{
	if (LocomotionState->PMC->bHasMoveInput)
	{
		// Run
		if (LocomotionState->PMC->IsRunRequested())
		{
			LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Run);
			return;
		}
	}
	// Idle
	else
	{
		LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Idle);
		return;
	}
}

void UPlayerWalkState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Walk"));
}
