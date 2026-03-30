// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"  // 젤 많이쓰는거니까 외우기
#include "NiagaraFunctionLibrary.h"  // 바로 include 하면 안디고, build.cs에 "Niagara" 추가해야함.


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Compoents
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;		// Root

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);
	Mesh->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 2000.f;
	Movement->ProjectileGravityScale = 0.0f;

	// Mesh Setup
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/0316/P38/SM_Rocket.SM_Rocket'"));
	if (SM_Body.Succeeded())
	{
		Mesh->SetStaticMesh(SM_Body.Object);
	}

	// box collider settup
	Box->SetBoxExtent(FVector(30, 10, 12));
}

void AMyActor::CalculateScoreWithDefault_Implementation(int InScore)
{
	// 기본 구현
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), InScore));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessActorBeginOverlap);
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::ProcessActorBeginOverlap(AActor* overlapped, AActor* ohterActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Process Actor Begin Overlap"));

	if (!ohterActor->ActorHasTag(FName(TEXT("Player"))))
	{
		// Effect
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation()
		);

		// Sound
		UGameplayStatics::SpawnSound2D(GetWorld(), ExplosionSound);

		// Scroe
		CalculateScoreWithDefault_Implementation(100);
		//CalculateScore(100);
	}
}