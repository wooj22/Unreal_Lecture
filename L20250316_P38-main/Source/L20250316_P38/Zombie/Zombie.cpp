#include "Zombie.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
	);
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

