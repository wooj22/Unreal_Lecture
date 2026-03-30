// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshcomponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // CameraBoom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->bUsePawnControlRotation = true;

    // FollowCamera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Mesh
    GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), 
        FRotator(0, -90.f, 0)
        );
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// EIC 생성 후 입력 바인딩
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Action Binding
    if (EIC)
    {
        EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);
        EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ATPSPlayer::Look);
        EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ACharacter::StopJumping);
        EIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ATPSPlayer::Zoom);
    }
}

// Input Action Handlers
void ATPSPlayer::Move(const FInputActionValue& Value)
{
	// [W],[S] : X축 이동, [A],[D] : Y축 이동
    FVector2D direction = Value.Get<FVector2D>();

    FVector newForwardVector = 
        UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));  

    FVector newRightVector =
        UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll));


	AddMovementInput(newForwardVector, direction.X);
	AddMovementInput(newRightVector, direction.Y);
}

void ATPSPlayer::Look(const FInputActionValue& Value)
{
    FVector2D direction = Value.Get<FVector2D>();

	//AddControllerPitchInput(direction.Y);     // 마우스 상하 이동 : Pitch
	AddControllerYawInput(direction.X);         // 마우스 좌우 이동 : Yaw
}

void ATPSPlayer::Zoom(const FInputActionValue& Value)
{
    float zoomValue = Value.Get<float>();

    // Zoom In / Out
    CameraBoom->TargetArmLength += zoomValue * 10.f;   // 줌 속도 조절 (10.f는 임의의 값)
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 100.f, 500.f); // 최소/최대 줌 거리 설정
}
