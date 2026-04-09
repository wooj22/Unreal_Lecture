// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputComponent;
class UPlayerFSMComponent;
class UPlayerMovementComponent;

/*
	[AMyPlayer : Character]

	- 컴포넌트 소유 및 초기화
	- 엔진 입력 바인딩 (입력 수신은 Player에서, 입력 해석과 처리는 FSM에서)
	- Tick에서 FSM 업데이트
*/

UCLASS()
class STUDY_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Generator
	AMyPlayer();

protected:
	// [ Life Cycle ]
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	// [ Functions ]
	void MoveInputMapping(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartRunInputMapping();
	void StopRunInputMapping();



public:
	// [ Compoennt ]
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UPlayerMovementComponent> PCM;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM")
	TObjectPtr<UPlayerFSMComponent> FSM;

	// [ Input Actions ]
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;
};
