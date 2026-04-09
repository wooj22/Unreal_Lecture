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

	// Sub FSM 평가
	EvaluateSubState();

	// Movement Apply
	float Speed = 0.f;
	switch (CurrentSubStateEnum)
	{
	case ELocomotionSubState::Walk:
		Speed = Player->MovementController->WalkSpeed;
		break;
	case ELocomotionSubState::Run:
		Speed = Player->MovementController->RunSpeed;
		break;
	}

	Player->MovementController->SetMovementSpeed(Speed);
	Player->MovementController->ApplyMoveInput();


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
	CurrentSubStateEnum = NewStateEnum;
	CurrentSubState = SubStates[(int32)CurrentSubStateEnum];

	// Enter
	if (CurrentSubState)
		CurrentSubState->OnEnter();
}

void UPlayerLocomotionState::EvaluateSubState()
{
	UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
	if (!CMC)
	{
		return;
	}

	// 이동 상태를 평가하고 하위 상태 전이
	const bool bIsFalling = PMC->bIsFalling;
	const float Speed2D = PMC->CurrentSpeed;
	const bool bHasMoveInput = PMC->bHasMoveInput;
	const bool bRunRequested = PMC->IsRunRequested();

	if (bIsFalling)
	{
		ChangeSubStateEnum(ELocomotionSubState::Fall);
		return;
	}

	if (Speed2D <= 3.0f)
	{
		ChangeSubStateEnum(ELocomotionSubState::Idle);
		return;
	}

	if (bHasMoveInput && bRunRequested)
	{
		ChangeSubStateEnum(ELocomotionSubState::Run);
		return;
	}

	if (bHasMoveInput)
	{
		ChangeSubStateEnum(ELocomotionSubState::Walk);
		return;
	}
}
