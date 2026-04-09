// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLocomotionBaseState.h"
#include "../MyPlayer.h"
#include "../PlayerFSMComponent.h"
#include "../MainState/PlayerLocomotionState.h"

void UPlayerLocomotionBaseState::Init(AMyPlayer* Player_, UPlayerFSMComponent* FSM_, UPlayerLocomotionState* LocomotionState_)
{
	this->Player = Player_;
	this->FSM = FSM_;
	this->LocomotionState = LocomotionState_;
}
