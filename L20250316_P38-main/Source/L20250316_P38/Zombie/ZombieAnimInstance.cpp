#include "ZombieAnimInstance.h"
#include "Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"

void UZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AZombie* Zombie = Cast<AZombie>(TryGetPawnOwner());
	if (Zombie)
	{
		CurrentState = Zombie->CurrentState;
		HP = Zombie->GetCharacterMovement()->Velocity.Size2D();
	}
}