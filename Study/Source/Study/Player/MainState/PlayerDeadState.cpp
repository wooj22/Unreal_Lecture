// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeadState.h"


void UPlayerDeadState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Enter Dead"));
}

void UPlayerDeadState::OnUpdate(float DeltaTime)
{
}

void UPlayerDeadState::OnExit()
{
	
}
