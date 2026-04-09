// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseState/PlayerBaseState.h"
#include "PlayerLocomotionState.generated.h"

class UPlayerLocomotionBaseState;


// Locomotion Sub State Enum
UENUM()
enum class ELocomotionSubState : uint8
{
	Idle,
	Walk,
	Run,
	Fall,
	Land,
	Count
};

/*
	플레이어 Main State : Locomotion State
	이동과 관련된 상태들을 관리합니다.

	** 하위 FSM을 운영합니다!
	Locomotion FSM - Idle, Walk, Run, Fall, Land

	Locomotion State에서 이동 시스템을 담당하고,
	하위 상태에서는 애니메이션, 사운드, 상태 변수 등 특수 행동 로직만 담당합니다.
	하위 FSM의 상태 전이는 각 상태에서가 아닌, Locomotion에서 판단하고 전이합니다.
*/

UCLASS()
class STUDY_API UPlayerLocomotionState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	// [ Life Cycle ]
	void Init(AMyPlayer* Player_, UPlayerFSMComponent* FSM_) override;  // 하위 FSM 초기화를 위해 override
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnExit() override;

	// [ Sub FSM ]
	void InitSubFSM();
	void ChangeSubStateEnum(ELocomotionSubState NewStateEnum);
	void EvaluateSubState();

	UPlayerLocomotionBaseState* GetCurrentSubState() const { return CurrentSubState; }
	ELocomotionSubState GetCurrentSubStateEnum() const { return CurrentSubStateEnum; }


private:
	// [ Functions ]
	// TODO..


private:
	UPROPERTY()
	TArray<TObjectPtr<UPlayerLocomotionBaseState>> SubStates;

	UPROPERTY()
	TObjectPtr<UPlayerLocomotionBaseState> CurrentSubState;

	UPROPERTY()
	ELocomotionSubState CurrentSubStateEnum = ELocomotionSubState::Count;
};
