// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.04f, FColor::Red, TEXT("Hello World!"));
		UE_LOG(LogTemp, Warning, TEXT("Hello Log"));
	}

	// 클래스명(MyPawn)으로 Pawn 등록
	DefaultPawnClass = AMyPawn::StaticClass();

	// 클래스명(MyPlayerController)으로 PlayerController 등록
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

