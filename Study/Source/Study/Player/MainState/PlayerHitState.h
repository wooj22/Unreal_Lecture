// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseState/PlayerBaseState.h"
#include "PlayerHitState.generated.h"


/*
	플레이어 Main State : Hit State
*/

UCLASS()
class STUDY_API UPlayerHitState : public UPlayerBaseState
{
	GENERATED_BODY()

public:
	void OnEnter() override;
	void OnUpdate(float DeltaTime) override;
	void OnExit() override;
};
