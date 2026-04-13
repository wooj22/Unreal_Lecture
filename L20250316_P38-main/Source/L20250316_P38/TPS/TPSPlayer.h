// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "TPSPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class AWeaponBase;
class UMaterialInstance;
class UParticleSystem;
class UAnimMontage;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unarmed = 0 UMETA(Display="Unarmed"),
	Pistol = 10 UMETA(Display = "Pistol"),
	Rifle = 20 UMETA(Display = "Rifle"),
	GrenadeLauncher = 30 UMETA(Display = "GrenadeLauncher"),
};


UCLASS()
class L20250316_P38_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Zoom(const FInputActionValue& Value);

	void Fire();

	void StartFire();

	void StopFire();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	uint8 bIsFire : 1 = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> FollorCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UChildActorComponent> Weapon;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_TPSMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_TPSJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_TPSLook;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_TPSZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_TPSFire;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EWeaponState CurrentWeapon;


	UFUNCTION(BlueprintCallable)
	void EquipItem(TSubclassOf<AWeaponBase> WeaponTemplate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<class AWeaponBase> DefalutWeapon;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> HitAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> ReloadAnimation;

	// TakeDamage Override
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
