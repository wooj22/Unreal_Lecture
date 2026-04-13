// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	if (GEngine)
	{ 
		GEngine->AddOnScreenDebugMessage(-1, 5.04f, FColor::Red, TEXT("Hello World"));

		UE_LOG(LogTemp, Warning, TEXT("안녕하세요."));
	}

	DefaultPawnClass = AMyPawn::StaticClass();

	PlayerControllerClass = AMyPlayerController::StaticClass();


}