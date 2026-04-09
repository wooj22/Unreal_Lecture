// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFSMComponent.generated.h"

class AMyPlayer;
class UPlayerBaseState;


// Player Main FSM State Enum
UENUM()
enum class EPlayerMainState : uint8
{
	Locomotion,		// 이동 계열 (하위 FSM 존재)
	Action,		    // 시작 - 행동 - 복귀 타임라인 구조의 행동 계열 (하위 FSM 존재)
	Hit,            // 피격
	Dead,			// 사망
	Count
};


/*
	[Player FSM Component : Actor Component]

	플레이어 HFSM 최상위 상태머신 돌리는 컴포넌트
	씬에 배치 정보를 가지지 않는 순수 로직 컴포넌트로, Actor Component를 상속받아 구현함
*/

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UPlayerFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Generator
	UPlayerFSMComponent();

	// [ FSM ]
	void InitFSM(AMyPlayer* Player_);
	void Update(float DeltaTime);
	void ChangeStateEnum(EPlayerMainState NewStateEnum);

	UPlayerBaseState* GetCurrentState() const { return CurrentState; }
	EPlayerMainState GetCurrentStateEnum() const { return CurrentStateEnum; }


	// [ Input ]
	//void SetMoveInput(const FVector2D& MoveInput_);
	//void SetLookInput(const FVector2D& LookInput_);
	//void SetRunRequested(bool bRunRequested_);
	//
	//const FVector2D& GetMoveInput() const { return MoveInput; }
	//bool IsRunRequested() const { return bRunRequested; }


	// [ Functions ]
	// TODO..


private:
	// [ Variables ]
	// Player
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AMyPlayer> OwnerPlayer;

	// States
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UPlayerBaseState>> States;

	// Cur State
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerBaseState> CurrentState;

	UPROPERTY(VisibleAnywhere)
	EPlayerMainState CurrentStateEnum = EPlayerMainState::Count;
};
