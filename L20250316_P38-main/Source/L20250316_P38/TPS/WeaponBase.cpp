// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "TPSPlayer.h"
#include "GameFramework/PlayerController.h"

AWeaponBase::AWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}


void AWeaponBase::Fire()
{
	ATPSPlayer* Player = Cast<ATPSPlayer>(GetOwner());
	if (!Player) return;

	FVector StartTrace = Player->FollorCamera->GetComponentLocation();
	FVector EndTrace;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
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

		// Shoot
		if (Result)
		{
			// Shoot Hit Decal Texture
			UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
				DecalTemplate,
				FVector(5.f, 5.f, 5.f),
				OutHit.ImpactPoint,
				OutHit.ImpactNormal.Rotation(),
				5.0f);

			if (Decal)
			{
				Decal->SetFadeScreenSize(0.005f);
			}

			// Damage
			UGameplayStatics::ApplyDamage(
				OutHit.GetActor(),
				10.0f,
				PC,
				this,
				UDamageType::StaticClass()  // BulletDemageType
			);

			// Effect
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				MuzzleFlashEffect,
				Mesh->GetSocketLocation(TEXT("Muzzle")),
				Mesh->GetSocketRotation(TEXT("Muzzle"))
			);

			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				HitEffect,
				Mesh->GetSocketLocation(TEXT("Muzzle")),
				Mesh->GetSocketRotation(TEXT("Muzzle"))
			);

			// Sound
			UGameplayStatics::SpawnSoundAtLocation(
				GetWorld(),
				FireSound,
				Mesh->GetSocketLocation(TEXT("Muzzle")),
				Mesh->GetSocketRotation(TEXT("Muzzle"))
			);
		}
	}
}