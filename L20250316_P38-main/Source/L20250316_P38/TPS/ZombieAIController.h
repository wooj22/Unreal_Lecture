// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception\AIPerceptionTypes.h"
#include "ZombieAIController.generated.h"


class UBehaviorTree;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class L20250316_P38_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:

	AZombieAIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAIPerceptionComponent> Perception;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UBehaviorTree> RunBTAsset;

	UFUNCTION()
	void ProcessTargetUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessTargetForgotten(AActor* Actor);

};
