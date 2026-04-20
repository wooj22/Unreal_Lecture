#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Zombie.h"
#include "BTService_GetDist.generated.h"

UENUM(BlueprintType)
enum class ECondition : uint8
{
	LessThan = 0 UMETA(DispalyName = "<"),
	GraterThan = 1 UMETA(DispalyName = ">")
};

UCLASS()
class L20250316_P38_API UBTService_GetDist : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_GetDist();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ECondition TargetCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EZombieState TargetState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float TargetDistance;
};
