// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UTPSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ATPSPlayer* Player = Cast<ATPSPlayer>(TryGetPawnOwner());

	// Animation Variables Update
	if (IsValid(Player))
	{
		Speed = Player->GetCharacterMovement()->Velocity.Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());
		CurrentWeapon = Player->CurrentWeapon;
	}
}
