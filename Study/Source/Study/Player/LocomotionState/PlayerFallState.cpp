// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFallState.h"

void UPlayerFallState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Fall"));
}

void UPlayerFallState::OnUpdate(float DeltaTime)
{
}

void UPlayerFallState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Fall"));
}
