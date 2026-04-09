// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovementComponent.h"
#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// GetCompoent
	Player = Cast<AMyPlayer>(GetOwner());
	Controller = Player->GetController();
	CharacterMovement = Player->GetCharacterMovement();
}

void UPlayerMovementComponent::SetMoveInput(const FVector2D& MoveInput_)
{
	MoveInput = MoveInput_;
}

void UPlayerMovementComponent::SetRunRequested(bool bRunRequested_)
{
	bRunRequested = bRunRequested_;
}

void UPlayerMovementComponent::SetMovementSpeed(float NewSpeed)
{
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = NewSpeed;
	}
}

void UPlayerMovementComponent::ApplyMoveInput()
{
	if (!Player || !Controller || !CharacterMovement)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerMovement nullptr!"));
		return;
	}

	if (MoveInput.IsNearlyZero())
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Player->AddMovementInput(Forward, MoveInput.Y);
	Player->AddMovementInput(Right, MoveInput.X);

	
}