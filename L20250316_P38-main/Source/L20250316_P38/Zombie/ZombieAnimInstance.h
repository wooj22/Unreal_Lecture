#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Zombie.h"

#include "ZombieAnimInstance.generated.h"


UCLASS()
class L20250316_P38_API UZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EZombieState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	uint8 HP = 100;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
