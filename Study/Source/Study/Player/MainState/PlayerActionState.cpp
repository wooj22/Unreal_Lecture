// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionState.h"

void UPlayerActionState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Enter Action"));
}

void UPlayerActionState::OnUpdate(float DeltaTime)
{
}

void UPlayerActionState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Exit Action"));
}
