// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBaseState.h"

void UPlayerBaseState::Init(AMyPlayer* Player_, UPlayerFSMComponent* FSM_)
{
	this->Player = Player_;
	this->FSM = FSM_;
}