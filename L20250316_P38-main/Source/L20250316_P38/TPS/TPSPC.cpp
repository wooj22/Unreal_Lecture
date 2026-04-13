// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPC.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void ATPSPC::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (IMC_Default)
				{
					InputSystem->AddMappingContext(IMC_Default, 0);
				}
			}
		}
	}
}
