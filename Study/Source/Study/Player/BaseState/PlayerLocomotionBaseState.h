// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerLocomotionBaseState.generated.h"

class AMyPlayer;
class UPlayerFSMComponent;
class UPlayerLocomotionState;


/*
	[UPlayerLocomotionBaseState : UObject]

	플레이어 Main FSM Locomotion 상태의 하위 상태 베이스 추상 클래스
	상태 종류 : Idle, Walk, Run, Fall, Land

	** 언리얼에서 FSM 구현시 주의사항
	- UCLASS(Abstract) : UHT에게 이 클래스는 추상 클래스임을 알림 (인스턴스화 불가)
	- =0 과같은 순수가상함수 표현은 UHT에서 인식하지 못하므로, PURE_VIRTUAL 매크로를 사용하여 순수가상함수임을 명시적으로 표현해야 함
*/

UCLASS(Abstract)
class STUDY_API UPlayerLocomotionBaseState : public UObject
{
	GENERATED_BODY()
	
public:
	// [LifeCycle]
	virtual void Init(AMyPlayer* Player_, UPlayerFSMComponent* FSM_, UPlayerLocomotionState* LocomotionState_);
	virtual void OnEnter() PURE_VIRTUAL(UPlayerLocomotionBaseState::OnEnter, );
	virtual void OnUpdate(float DeltaTime) PURE_VIRTUAL(UPlayerLocomotionBaseState::OnUpdate, );
	virtual void OnExit() PURE_VIRTUAL(UPlayerLocomotionBaseState::OnExit, );

protected:
	UPROPERTY()
	TObjectPtr<AMyPlayer> Player;

	UPROPERTY()
	TObjectPtr<UPlayerFSMComponent> FSM;

	UPROPERTY()
	TObjectPtr<UPlayerLocomotionState> LocomotionState;
};
