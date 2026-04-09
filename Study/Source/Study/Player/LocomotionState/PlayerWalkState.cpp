// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWalkState.h"

void UPlayerWalkState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Walk"));
}

void UPlayerWalkState::OnUpdate(float DeltaTime)
{
}

void UPlayerWalkState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Walk"));
}
