// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/GameplayStatics.h"  // 젤 많이쓰는거니까 외우기


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create components
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;		// Root

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	// Mesh Setup
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/0316/P38/SM_P38_Body.SM_P38_Body'"));
	if(SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/0316/P38/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	// Location setup
	Left->SetRelativeLocation(FVector(35, 22, 0));
	Right->SetRelativeLocation(FVector(35, -22, 0));
	Arrow->SetRelativeLocation(FVector(100, 0, 0));
	Camera->SetRelativeRotation(FRotator(0, -10, 0));
	Camera->SetRelativeRotation(FRotator(0, -10, 0));

	// box collider settup
	Box->SetBoxExtent(FVector(32, 32, 32));

	// Movement setup
	Movement->MaxSpeed = 1200.f;

	// Spring Arm setup
	SpringArm->TargetArmLength = 120.f;
	SpringArm->SocketOffset.Z = 1.5f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// movement
	AddMovementInput(GetActorForwardVector());

	// propeller rotation
	RotatePropeller(Left);
	RotatePropeller(Right);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Shoot);
}

void AMyPawn::Pitch(float axis)
{
	float locationSpeed = 90.0f;

	this->AddActorLocalRotation(FRotator(
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * axis * locationSpeed,
		0, 0));
}

void AMyPawn::Roll(float axis)
{
	float locationSpeed = 90.0f;

	this->AddActorLocalRotation(FRotator(0, 0,
		UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * axis * locationSpeed));
}

// 프로펠러 회전 연출
void AMyPawn::RotatePropeller(UStaticMeshComponent* where)
{
	float delta = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	float speed = 2880.f;

	where->AddLocalRotation(FRotator(delta * speed, 0, 0));
}

// Input Action "Fire" 이벤트시 액터 생성
void AMyPawn::Shoot()
{
	GetWorld()->SpawnActor<AActor>(AMyActor::StaticClass(),
		Arrow->K2_GetComponentToWorld());
}

