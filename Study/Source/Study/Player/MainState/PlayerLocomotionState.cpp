// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLocomotionState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../MyPlayer.h"
#include "../PlayerMovementComponent.h"
#include "../PlayerFSMComponent.h"

#include "../BaseState/PlayerLocomotionBaseState.h"
#include "../LocomotionState/PlayerIdleState.h"
#include "../LocomotionState/PlayerWalkState.h"
#include "../LocomotionState/PlayerRunState.h"
#include "../LocomotionState/PlayerFallState.h"
#include "../LocomotionState/PlayerLandState.h"

void UPlayerLocomotionState::Init(AMyPlayer* Player_, UPlayerFSMComponent* FSM_)
{
	Super::Init(Player_, FSM_);

	PMC = Player_->FindComponentByClass<UPlayerMovementComponent>();
	if (!PMC) UE_LOG(LogTemp, Warning, TEXT("[UPlayerLocomotionState] PMC nullptr!"));
	
	InitSubFSM();
}

void UPlayerLocomotionState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("[Player FSM] Enter Locomotion"));
	ChangeSubStateEnum(ELocomotionSubState::Idle);
}

void UPlayerLocomotionState::OnUpdate(float DeltaTime)
{
	if (!Player || !FSM)
	{
		return;
	}

	// Locomotion 공용 상위 트랜지션 (나머지는 하위 State에서 전이)
	TryGlobalTransition();

	// Movement Apply
	float Speed = 0.f;
	switch (CurrentSubStateEnum)
	{
	case ELocomotionSubState::Walk:
		Speed = Player->PCM->WalkSpeed;
		break;
	case ELocomotionSubState::Run:
		Speed = Player->PCM->RunSpeed;
		break;
	}

	Player->PCM->SetMovementSpeed(Speed);
	Player->PCM->ApplyMoveInput();


	// Update Locomotion FSM
	if (CurrentSubState)
	{
		CurrentSubState->OnUpdate(DeltaTime);
	}
}

void UPlayerLocomotionState::OnExit()
{
	if (CurrentSubState)
	{
		CurrentSubState->OnExit();
	}

	UE_LOG(LogTemp, Log, TEXT("[Player FSM] Exit Locomotion"));
}

void UPlayerLocomotionState::InitSubFSM()
{
	// Size Init
	SubStates.SetNum((int32)ELocomotionSubState::Count);

	// Create State
	SubStates[(int32)ELocomotionSubState::Idle] = NewObject<UPlayerIdleState>(this);
	SubStates[(int32)ELocomotionSubState::Walk] = NewObject<UPlayerWalkState>(this);
	SubStates[(int32)ELocomotionSubState::Run]  = NewObject<UPlayerRunState>(this);
	SubStates[(int32)ELocomotionSubState::Fall] = NewObject<UPlayerFallState>(this);
	SubStates[(int32)ELocomotionSubState::Land] = NewObject<UPlayerLandState>(this);

	// SubState Init
	for (int i = 0; i < (int32)ELocomotionSubState::Count; ++i)
	{
		if (SubStates[i])
			SubStates[i]->Init(Player, FSM, this);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Locomotion SubFSM Initialized"));

	// Cur SubState Init (아직 상위 FSM이 초기화되는중이라 진입은 x)
	CurrentSubState = nullptr;
	CurrentSubStateEnum = ELocomotionSubState::Count;
}

void UPlayerLocomotionState::ChangeSubStateEnum(ELocomotionSubState NewStateEnum)
{
	// Check Same State
	if (NewStateEnum == CurrentSubStateEnum)
		return;

	// Exit
	if (CurrentSubState)
		CurrentSubState->OnExit();

	// Change State
	PreviousSubState = CurrentSubState;
	PreviousSubStateEnum = CurrentSubStateEnum;
	CurrentSubStateEnum = NewStateEnum;
	CurrentSubState = SubStates[(int32)CurrentSubStateEnum];

	// Enter
	if (CurrentSubState)
		CurrentSubState->OnEnter();
}

void UPlayerLocomotionState::TryGlobalTransition()
{
	UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
	if (!CMC) return;

	// 공용? Locomotion Transition
	// Fall
	if (PMC->bIsFalling && CurrentSubStateEnum != ELocomotionSubState::Fall)
	{
		ChangeSubStateEnum(ELocomotionSubState::Fall);
		return;
	}

	// Land
	if (CurrentSubStateEnum == ELocomotionSubState::Fall && !PMC->bIsFalling)
	{
		ChangeSubStateEnum(ELocomotionSubState::Land);
		return;
	}
}
