// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "TPSPlayer.h"

#include "TPSAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20250316_P38_API UTPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float Speed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Direction = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EWeaponState CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AimYaw = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AimPitch = 0;

};
