// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLandState.h"
#include "../MainState/PlayerLocomotionState.h"
#include "../PlayerMovementComponent.h"

void UPlayerLandState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Land"));

	LandProgressTime = 0.0f;
}

void UPlayerLandState::OnUpdate(float DeltaTime)
{
	// LandProgressTime 뒤 Idle   
	// TODO :: 애니메이션 넣으면 애니메이션 끝나는 이벤트 기반으로 수정
	LandProgressTime += DeltaTime;
	if (LandProgressTime >= LandingTime)
	{
		LocomotionState->ChangeSubStateEnum(ELocomotionSubState::Idle);
	}
}

void UPlayerLandState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Land"));
}
