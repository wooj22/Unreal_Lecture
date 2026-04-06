// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSPlayer.h"
#include "TPSAnimInstance.generated.h"

/*
	[TPS AnimInstance]
	AnimInstance´Â
*/

UCLASS()
class THIRDPERSON_API UTPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// [Lifecycle]
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// [Variables]
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	EWeaponState CurrentWeapon;
};
