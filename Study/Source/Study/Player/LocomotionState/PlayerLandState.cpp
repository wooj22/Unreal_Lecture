// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLandState.h"

void UPlayerLandState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Land"));
}

void UPlayerLandState::OnUpdate(float DeltaTime)
{
}

void UPlayerLandState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Land"));
}
