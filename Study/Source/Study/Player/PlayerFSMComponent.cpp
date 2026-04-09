// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFSMComponent.h"
#include "MyPlayer.h"
#include "BaseState/PlayerBaseState.h"
#include "MainState/PlayerLocomotionState.h"
#include "MainState/PlayerActionState.h"
#include "MainState/PlayerHitState.h"
#include "MainState/PlayerDeadState.h"


UPlayerFSMComponent::UPlayerFSMComponent()
{
	PrimaryComponentTick.bCanEverTick = false;			// Tick 사용 x
}

void UPlayerFSMComponent::InitFSM(AMyPlayer* Player_)
{
	// Player Set
	this->OwnerPlayer = Player_;

	// Enum Index기반 초기화
	States.SetNum((int32)EPlayerMainState::Count);

	// Create State
	States[(int32)EPlayerMainState::Locomotion] = NewObject<UPlayerLocomotionState>(this);
	States[(int32)EPlayerMainState::Action]		= NewObject<UPlayerActionState>(this);
	States[(int32)EPlayerMainState::Hit]		= NewObject<UPlayerHitState>(this);
	States[(int32)EPlayerMainState::Dead]	    = NewObject<UPlayerDeadState>(this);

	// State Init
	for (int32 i = 0; i < (int32)EPlayerMainState::Count; ++i)
	{
		if (States[i]) 
			States[i]->Init(OwnerPlayer, this);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Main FSM Initialized"));

	// Cur State Init
	CurrentState = nullptr;
	CurrentStateEnum = EPlayerMainState::Count;
	ChangeStateEnum(EPlayerMainState::Locomotion);
}

void UPlayerFSMComponent::Update(float DeltaTime)
{
	// State Update
	if (CurrentState)
		CurrentState->OnUpdate(DeltaTime);
}

void UPlayerFSMComponent::ChangeStateEnum(EPlayerMainState NewStateEnum)
{
	// Check Same State
	if (NewStateEnum == CurrentStateEnum)
		return;

	// Exit
	if (CurrentState)
		CurrentState->OnExit();

	// Change State
	CurrentStateEnum = NewStateEnum;
	CurrentState = States[(int32)CurrentStateEnum];

	// Enter
	if (CurrentState)
		CurrentState->OnEnter();
}