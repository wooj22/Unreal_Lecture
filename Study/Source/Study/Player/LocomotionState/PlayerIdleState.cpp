// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIdleState.h"
#include "../MainState/PlayerLocomotionState.h"
#include "../PlayerMovementComponent.h"

void UPlayerIdleState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Idle"));
}

void UPlayerIdleState::OnUpdate(float DeltaTime)
{
	if (LocomotionState->PMC->bHasMoveInput)
	{
		// Run
		if (LocomotionState->PMC->IsRunRequested())
		{
			LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Run);
			return;
		}
		// Walk
		else
		{
			LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Walk);
			return;
		}
	}
}

void UPlayerIdleState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Idle"));
}
