// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"

class AMyPlayer;
class AController;
class UCharacterMovementComponent;

/*
	캐릭터 무브먼트 컨르톨 컴포너트
	Character Movement Component를 래핑한다고 생각하면 됨
	FSM 특히 Locomotion에서 해당 컴포넌트를 통해 이동 명령을 내림

	- 입력 저장
	- 실제 이동 적용
	- 속도 세팅
	- 점프 / 달리기 / 회전 처리
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDY_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// [ Component Ref ]
	AMyPlayer* Player;
	AController* Controller;
	UCharacterMovementComponent* CharacterMovement;

public:	
	UPlayerMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	// [ Input Recive ]
	void SetMoveInput(const FVector2D& MoveInput_);
	void SetRunRequested(bool bRunRequested_);

	const FVector2D& GetMoveInput() const { return MoveInput; }
	bool IsRunRequested() const { return bRunRequested; }

	// [ Movement Control ]
	void SetMovementSpeed(float NewSpeed);
	void ApplyMoveInput();


public:	
	// [ Movement Values ]
	UPROPERTY()
	float WalkSpeed = 600.0f;

	UPROPERTY()
	float RunSpeed = 800.0f;


	// [ Input ]
	UPROPERTY()
	FVector2D MoveInput = FVector2D::ZeroVector;

	UPROPERTY()
	FVector2D LookInput = FVector2D::ZeroVector;

	UPROPERTY()
	bool bRunRequested = false;
};
