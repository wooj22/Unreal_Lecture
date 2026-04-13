// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollorCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollorCamera"));
	FollorCamera->SetupAttachment(CameraBoom);

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
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

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC)
	{
		EIC->BindAction(IA_TPSMove, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);

		EIC->BindAction(IA_TPSJump, ETriggerEvent::Triggered, this, &ATPSPlayer::Jump);

		EIC->BindAction(IA_TPSJump, ETriggerEvent::Canceled, this, &ATPSPlayer::StopJumping);

		EIC->BindAction(IA_TPSLook, ETriggerEvent::Triggered, this, &ATPSPlayer::Look);

		EIC->BindAction(IA_TPSZoom, ETriggerEvent::Triggered, this, &ATPSPlayer::Zoom);

		EIC->BindAction(IA_TPSFire, ETriggerEvent::Triggered, this, &ATPSPlayer::Fire);
	}
}

void ATPSPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();


	FVector NewForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));

	FVector NewRightVector = UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll));

	AddMovementInput(NewForwardVector * Direction.X);
	AddMovementInput(NewRightVector * Direction.Y);
}

void ATPSPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	AddControllerPitchInput(Direction.Y);
	AddControllerYawInput(Direction.X);
	
}

void ATPSPlayer::Zoom(const FInputActionValue& Value)
{
	float Zoom = Value.Get<float>();

	CameraBoom->TargetArmLength += (Zoom*30.f);

	UKismetMathLibrary::Clamp(CameraBoom->TargetArmLength, 30.0f, 600.0f);
}

void ATPSPlayer::EquipItem(TSubclassOf<AWeaponBase> WeaponTemplate)
{
	//WeaponTemplate 클래스 이름을 의미함, 리플렉션에서 클래스 이름으로 생성 하는 로직
	//단 CPP은 클래스 이름이 없어서 CDO가지고 생성함
	Weapon->SetChildActorClass(WeaponTemplate);

	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		switch (ChildWeapon->WeaponType)
		{
			case EWeaponState::Pistol:
			{
				ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
				ChildWeapon->SetOwner(this);
				CurrentWeapon = ChildWeapon->WeaponType;
				break;
			}
		}
		switch (ChildWeapon->WeaponType)
		{
			case EWeaponState::Rifle:
			{
				ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
				ChildWeapon->SetOwner(this);
				CurrentWeapon = ChildWeapon->WeaponType;
				break;
			}
		}
	}
}

void ATPSPlayer::Fire()
{

	FVector StartTrace = FollorCamera->GetComponentLocation();
	FVector EndTrace;

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		int32 ScreenSizeX = 0;
		int32 ScreenSizeY = 0; 
		FVector WorldLocation;
		FVector WorldDirection;

		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
		PC->DeprojectScreenPositionToWorld(ScreenSizeX / 2, ScreenSizeY / 2, WorldLocation, WorldDirection);

		EndTrace = StartTrace + (WorldDirection * 100000.f);

		TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);

		FHitResult OutHit;

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			StartTrace,
			EndTrace,
			Objects,
			true,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			OutHit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			5.0f);
		if (Result)
		{

		}
	}
}

void ATPSPlayer::StartFire()
{
}

void ATPSPlayer::StopFire()
{
}
