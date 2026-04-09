// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRunState.h"
#include "../MainState/PlayerLocomotionState.h"
#include "../PlayerMovementComponent.h"

void UPlayerRunState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Run"));
}

void UPlayerRunState::OnUpdate(float DeltaTime)
{
	if (LocomotionState->PMC->bHasMoveInput)
	{
		// Walk
		if (!LocomotionState->PMC->IsRunRequested())
		{
			LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Walk);
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

void UPlayerRunState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Run"));
}
