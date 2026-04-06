// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TPSPlayer.generated.h"  // generated include는 무조건 마지막!


class USpringArmComponent;
class UCameraComponent;
class UInputAction;


// Enum - Weapon State
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unarmed = 0 UMETA(Display = "Unarmed"),
	Pistol = 1 UMETA(Display = "Pistol"),
	Rifle = 2 UMETA(Display = "Rifle"),
	GrenadeLauncher = 0 UMETA(Display = "GrenadeLauncher")
};


UCLASS()
class THIRDPERSON_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// [ Compoenents ]
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	// [ Input Actions ]
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Zoom;

	// [ Variables ]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponState CurrentWeapon = EWeaponState::Unarmed;

	
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// [ Lifecycle ]
	virtual void BeginPlay() override;


public:	
	// [ Lifecycle ]
	virtual void Tick(float DeltaTime) override;

	
	// [ Input ]
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Action Handlers
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
};
