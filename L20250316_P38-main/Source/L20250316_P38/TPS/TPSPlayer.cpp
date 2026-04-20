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
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "BulletDamageType.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

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

	StimuliSoruce = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSoruce"));

	SetGenericTeamId(2);
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

		EIC->BindAction(IA_TPSFire, ETriggerEvent::Triggered, this, &ATPSPlayer::StartFire);

		EIC->BindAction(IA_TPSFire, ETriggerEvent::Completed, this, &ATPSPlayer::StopFire);
		EIC->BindAction(IA_TPSFire, ETriggerEvent::Canceled, this, &ATPSPlayer::StopFire);

		EIC->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &ATPSPlayer::Reload);

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

float ATPSPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	FString Temp = FString::Printf(TEXT("Hit0%d_Start"), FMath::RandRange(1, 3));

	UE_LOG(LogTemp, Warning, TEXT("Damage %s"), *Temp);
	
	PlayAnimMontage(HitAnimaion,
		1.0f,
		FName(Temp)
	);

	return DamageAmount;
}

void ATPSPlayer::Fire()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Fire();
	}
	
}

void ATPSPlayer::StartFire()
{
	bIsFire = true;
	Fire();
}

void ATPSPlayer::StopFire()
{
	bIsFire = false;
}


void ATPSPlayer::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));


	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		switch (ChildWeapon->WeaponType)
		{
			case EWeaponState::Pistol:
			{
				PlayAnimMontage(ReloadAnimation,
					1.0f,
					FName("Pistol")
				);
				break;
			}
			case EWeaponState::Rifle:
			{
				PlayAnimMontage(ReloadAnimation,
					1.0f,
					FName("Rifle")
				);
				break;
			}
		}
	}
}