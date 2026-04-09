// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHitState.h"

void UPlayerHitState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Enter Hit"));
}

void UPlayerHitState::OnUpdate(float DeltaTime)
{
}

void UPlayerHitState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Exit Hit"));
}
