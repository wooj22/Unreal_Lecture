// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseState/PlayerBaseState.h"
#include "PlayerDeadState.generated.h"


/*
	플레이어 Main State : Dead State
	
*/

UCLASS()
class STUDY_API UPlayerDeadState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnExit() override;
};
