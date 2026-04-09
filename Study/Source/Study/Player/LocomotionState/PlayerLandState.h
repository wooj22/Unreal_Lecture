// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseState/PlayerLocomotionBaseState.h"
#include "PlayerLandState.generated.h"


/*
	플레이어 Locomotion Sub State : Land State
*/

UCLASS()
class STUDY_API UPlayerLandState : public UPlayerLocomotionBaseState
{
	GENERATED_BODY()

public:
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnExit() override;
};
