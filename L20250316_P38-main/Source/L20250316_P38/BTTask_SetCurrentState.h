// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TPS/Zombie.h"

#include "BTTask_SetCurrentState.generated.h"

/**
 * 
 */
UCLASS()
class L20250316_P38_API UBTTask_SetCurrentState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EZombieState CurrentState;
};
