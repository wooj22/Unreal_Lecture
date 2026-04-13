// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h" //important
#include "NiagaraFunctionLibrary.h"

// Sets default values
//CDO 초기화
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	Body->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 1000.0f;
	Movement->InitialSpeed = 1000.f;
	Movement->ProjectileGravityScale = 0.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/p38/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessActorBeginOverlap);
	
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("%d %s"), 11, TEXT("Hello"));


	if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == false)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplosionTemplate,
			GetActorLocation()
		);

		UGameplayStatics::SpawnSound2D(GetWorld(),
			ExplosionSound
		);

		//CalculateScore(100);
		CalculateScoreWithDefault(200);
	}
}

void AMyRocket::CalculateScoreWithDefault_Implementation(int InScore)
{
	//기본 구현
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("적으라고 이색휘야"));
}

void AMyRocket::ServerCPPFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("In CPP"));
}

