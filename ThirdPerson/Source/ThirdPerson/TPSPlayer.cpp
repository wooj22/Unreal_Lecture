// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshcomponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"


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

	// CHildActorComponent - Weapon
    Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(GetMesh());


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
    
	EquipItem(DefalutWeapon);
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
        EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ATPSPlayer::Fire);
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

	AddControllerPitchInput(direction.Y);     // 마우스 상하 이동 : Pitch
	AddControllerYawInput(direction.X);         // 마우스 좌우 이동 : Yaw
}

void ATPSPlayer::Zoom(const FInputActionValue& Value)
{
    float zoomValue = Value.Get<float>();

    // Zoom In / Out
    CameraBoom->TargetArmLength += zoomValue * 10.f;   // 줌 속도 조절 (10.f는 임의의 값)
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 100.f, 500.f); // 최소/최대 줌 거리 설정
}

void ATPSPlayer::Fire(const FInputActionValue& Value)
{

}

void ATPSPlayer::EquipItem(TSubclassOf<AWeaponBase> WeaponTemplate)
{

	// Pickup된 아이템 Get
	// WeaponTemplate->GetClass() -> 클래스 이름임. 리플렉션에서 클래스 이름으로 객체를 생성할 수 있음.
	// CPP는 클래스 이름이 없어서 CDO에서 클래스 이름을 가져와야 함. CDO는 클래스의 기본 객체로, 클래스의 기본 속성을 가지고 있음.
    Weapon->SetChildActorClass(WeaponTemplate->GetClass());  

    // 아이템이 WeaponBase라면
    AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());

    // ChildCompoent로 Attach
    if (ChildWeapon)
    {
        switch (ChildWeapon->WeaponType)
        {
            case EWeaponState::Pistol:
            case EWeaponState::Rifle:
            {
                ChildWeapon->AttachToComponent(GetMesh(),
                    FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
                ChildWeapon->SetOwner(this);
                CurrentWeapon = ChildWeapon->WeaponType;

                break;
            }
        }
    }
}

void ATPSPlayer::Fire()
{
    // 총알 발사 위치
    FVector StartTrace = FollowCamera->GetComponentLocation();
    FVector EndTrace;

    APlayerController* PC = Cast<APlayerController>(GetController());

    if (PC)
    {
        // 스크린 중앙 좌표의 월드 좌표 Get
        int32 ViewportSizeX, ViewportSizeY;
        FVector WorldLocation, WorldDirection;

        PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
        PC->DeprojectScreenPositionToWorld
        (ViewportSizeX / 2, ViewportSizeY / 2,   // Screen Position
            WorldLocation, WorldDirection);      // World 위치과 방향을 얻음

        
        EndTrace = StartTrace + (WorldDirection * 10000.f);

		// 충돌할 객체의 타입 설정 (Pawn, WorldStatic, WorldDynamic)
		TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

		// 무시할 액터 설정 (자신과 자신의 무기)
        TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);

        // Hit 결과
        FHitResult OutHits;

        // LineTrace (Laycast)
        bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
            GetWorld(),
            StartTrace,     // 광선 시작점
            EndTrace,       // 광선 끝점
			Objects,        // 충돌할 객체의 타입
			true,           // bTraceComplex : true로 설정하면 더 정확한 충돌 감지가 가능하지만 성능에 영향을 줄 수 있음
			IgnoreActors,   // 무시할 액터
			EDrawDebugTrace::ForDuration,   // 디버그용으로 광선을 화면에 표시
			OutHits,                        // Hit 결과를 저장할 변수
			true,                           // 충돌한 액터의 이름을 화면에 표시
            FLinearColor::Red,              // 광선 색상
			FLinearColor::Green,            // 충돌 지점 색상
			5.0f                            // 광선이 화면에 표시되는 시간
        );

        if (Result)
        {
            // Hit된 액터 존재
        }
    }
}

void ATPSPlayer::StartFire()
{
}

void ATPSPlayer::StopFire()
{
}
