// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"


UENUM(BlueprintType)
enum class EZombieState : uint8
{
	Idle			= 0 UMETA(DisplayName = "Idle"),
	Chase			= 1 UMETA(DisplayName = "Chase"),
	Battle			= 2 UMETA(DisplayName = "Battle"),
	Death			= 3 UMETA(DisplayName = "Death")
};


UCLASS()
class L20250316_P38_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EZombieState CurrentState;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	uint8 HP = 100;
};
