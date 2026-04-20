// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTService_GetDist.h"
#include "BTTask_CheckDist.generated.h"

/**
 * 
 */
UCLASS()
class L20250316_P38_API UBTTask_CheckDist : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckDist();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ECondition TargetCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EZombieState TargetState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float TargetDistance;
};
