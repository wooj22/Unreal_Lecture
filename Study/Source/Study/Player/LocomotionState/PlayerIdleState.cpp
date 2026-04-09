// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIdleState.h"

void UPlayerIdleState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Idle"));
}

void UPlayerIdleState::OnUpdate(float DeltaTime)
{
}

void UPlayerIdleState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Idle"));
}
