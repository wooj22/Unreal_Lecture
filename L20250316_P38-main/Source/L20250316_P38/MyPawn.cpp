// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h" //important
#include "MyRocket.h"
#include "NiagaraFunctionLibrary.h"


// CDO Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CDO √ ±‚»≠

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

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


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/p38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/p38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(35.976219f, -20.291702f, 0.970738f));
	Right->SetRelativeLocation(FVector(35.976219f, 20.291702f, 0.970738f));

	Movement->MaxSpeed = 0;


	static ConstructorHelpers::FClassFinder<AMyRocket> RocketBP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/CPP/BP_MyRocket.BP_MyRocket_C'"));
	if (RocketBP.Succeeded())
	{
		RocketTemplate = RocketBP.Class;
	}


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

	AddMovementInput(GetActorForwardVector());
	
	RotatePropeller(Left);
	RotatePropeller(Right);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyPawn::Fire);

}

void AMyPawn::Fire()
{
	GetWorld()->SpawnActor<AActor>(RocketTemplate,
		Arrow->K2_GetComponentToWorld());
}


void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * Value * 90.0f, 0, 0));
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0, 0, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * Value * 90.0f));
}

void AMyPawn::RotatePropeller(USceneComponent* Where)
{
	Where->AddLocalRotation(FRotator(0, 0, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 7200.0f));
}

