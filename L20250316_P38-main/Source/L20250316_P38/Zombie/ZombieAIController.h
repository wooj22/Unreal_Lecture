#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

class UBehaviorTree;


UCLASS()
class L20250316_P38_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AZombieAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UBehaviorTree> RunBTAsset;
};
