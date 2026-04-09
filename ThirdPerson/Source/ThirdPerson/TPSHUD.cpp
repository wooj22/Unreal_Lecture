// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHUD.h"
#include "Engine/Canvas.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATPSHUD::DrawHUD()
{
	Super::DrawHUD();

	ATPSPlayer* Player = Cast<ATPSPlayer>(GetOwningPawn());
	
	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;

	int32 UniX = Canvas->SizeX / 100;
	int32 DrawSize = UniX * 2;
	
	float GrabRatio = 0;
	int Gap = UniX * 3;

	if (Player)
	{
		int32 MaxSpeed = Player->GetCharacterMovement()->GetMaxSpeed();
		int32 CurrentSpeed = Player->GetCharacterMovement()->Velocity.Size2D();

		GrabRatio = (float)CurrentSpeed / (float)MaxSpeed;
	}

	Gap = Gap * GrabRatio;

	// 가로 십자축
	Draw2DLine(CenterX - DrawSize - Gap, CenterY, CenterX - Gap, CenterY, FColor::Green);
	Draw2DLine(CenterX + Gap, CenterY, CenterX + DrawSize + Gap, CenterY, FColor::Green);
	
	// 세로 십자축
	Draw2DLine(CenterX, CenterY - DrawSize - Gap, CenterX, CenterY - Gap, FColor::Green);
	Draw2DLine(CenterX, CenterY + Gap, CenterX, CenterY + DrawSize + Gap, FColor::Green);
}
