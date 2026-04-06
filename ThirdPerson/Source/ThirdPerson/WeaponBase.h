// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "TPSPlayer.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THIRDPERSON_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()
	
public:
	// General
	AWeaponBase();

	// [Components]
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	// [Vartiables]
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	FName SocketName = TEXT("HandGrip_R");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponState WeaponType;
};
