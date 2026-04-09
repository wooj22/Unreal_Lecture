// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseState/PlayerBaseState.h"
#include "PlayerActionState.generated.h"


/*
	플레이어 Main State : Action State
	시작-행동-복귀의 타임라인 구조를 공유하는 액션 계열 상태들을 관리합니다.

	** 하위 FSM을 운영합니다!
	Action FSM - Attack, Dodge, UseItem
*/

UCLASS()
class STUDY_API UPlayerActionState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnExit() override;
};
