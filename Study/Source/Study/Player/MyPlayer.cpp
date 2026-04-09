// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Components/InputComponent.h"

#include "PlayerMovementComponent.h"
#include "PlayerFSMComponent.h"



AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// [ Add Component ]
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));	
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	PCM = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("MovementController"));
	FSM = CreateDefaultSubobject<UPlayerFSMComponent>(TEXT("FSM"));

	// [ Init ]
	// Camera
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;	// SpringArm이 컨트롤 회전을 따라 회전 (On : Controller기준 / Off : 부모 기준)
	Camera->bUsePawnControlRotation = false;	// 카메라는 따로 컨트롤 회전을 먹지 않음 

	// Movement
	UCharacterMovementComponent* cmc = GetCharacterMovement();

	// 캐릭터가 Controller 회전에 영향을 받지 않고 스스로의 무브먼트에 따라 회전하도록
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	cmc->bOrientRotationToMovement = true;				// ture : 이동 방향으로 회전, false : 자동 회전 x
	cmc->RotationRate = FRotator(0.0f, 720.0f, 0.0f);	// 이동 방향 회전시, 초당 회전 속도

	// 기본 이동값
	cmc->MaxWalkSpeed = PCM->WalkSpeed;					// 걷기 최대 속도
	cmc->MaxWalkSpeedCrouched = PCM->WalkSpeed / 2;		// 웅크리고 걷기 최대 속도
	cmc->MinAnalogWalkSpeed = PCM->AnalogWalkSpeed / 3;  // 살짝 이동시 속도 (패드를 살짝 밀었을때)

	// 공중제어
	cmc->GravityScale = 1.5f;		// 중력 배율
	cmc->AirControl = PCM->AirControl;		// 공중 방향 조절 정도 (0이면 공중제어 x, 높은수록 방향전환 쉬움)

	// 물리
	cmc->MaxAcceleration = PCM->MaxAcceleration;		    // 현재속도에서 목표속도로 가속하는 정도
	cmc->BrakingDecelerationWalking = PCM->BrakingDecelerationWalking;	// 이동을 멈출떄 감속하는 힘
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Controller 회전값 Clamp
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PC->PlayerCameraManager)
		{
			PC->PlayerCameraManager->ViewPitchMin = -45.f;
			PC->PlayerCameraManager->ViewPitchMax = 70.f;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("PlayerCameraManager Setting Failed"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerCameraManager Setting Failed"));
	}

	// FSM Init
	if (FSM)
	{
		FSM->InitFSM(this);
	}
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FSM Update
	if(FSM)
	{
		FSM->Update(DeltaTime);
	}
}

void AMyPlayer::MoveInputMapping(const FInputActionValue& Value)
{
	if (PCM)
	{
		PCM->SetMoveInput(Value.Get<FVector2D>());
	}
}

void AMyPlayer::Look(const FInputActionValue& Value)
{
	// Look만 Player에서 조작하는 이유.
	// Input → Controller(ControlRotation) → (옵션에 따라) Pawn / Camera / SpringArm

	FVector2D LookValue = Value.Get<FVector2D>();
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);

	//UE_LOG(LogTemp, Warning, TEXT("LookValue X: %.2f Y: %.2f"), LookValue.X, LookValue.Y);
	//
	//if (Controller)
	//{
	//	const FRotator CR = Controller->GetControlRotation();
	//	UE_LOG(LogTemp, Warning, TEXT("Yaw: %.2f Pitch: %.2f"), CR.Yaw, CR.Pitch);
	//}
}

void AMyPlayer::StartRunInputMapping()
{
	if(PCM)
	{
		PCM->SetRunRequested(true);
	}
}

void AMyPlayer::StopRunInputMapping()
{
	if (PCM)
	{
		PCM->SetRunRequested(false);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input Action 바인딩
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Move)
			EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyPlayer::MoveInputMapping);
			EnhancedInput->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMyPlayer::MoveInputMapping);
			EnhancedInput->BindAction(IA_Move, ETriggerEvent::Canceled, this, &AMyPlayer::MoveInputMapping);
		
		if (IA_Look)
			EnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		
		if (IA_Run) {
			EnhancedInput->BindAction(IA_Run, ETriggerEvent::Triggered, this, &AMyPlayer::StartRunInputMapping);
			EnhancedInput->BindAction(IA_Run, ETriggerEvent::Completed, this, &AMyPlayer::StopRunInputMapping);
			EnhancedInput->BindAction(IA_Run, ETriggerEvent::Canceled, this, &AMyPlayer::StopRunInputMapping);
		}
	}
}

