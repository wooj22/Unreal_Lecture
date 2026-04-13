// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "TPSPlayer.h"

#include "WeaponBase.generated.h"

/**
 *
 */
UCLASS()
class L20250316_P38_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName SocketName = TEXT("HandGrip_R");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EWeaponState WeaponType;
};
