// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRunState.h"

void UPlayerRunState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Enter Run"));
}

void UPlayerRunState::OnUpdate(float DeltaTime)
{
}

void UPlayerRunState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player Sub FSM] Exit Run"));
}
