// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPC.h"
#include "InputMappingContext.h"     // plugin 처리 필요
#include "EnhancedInputSubsystems.h"


void ATPSPC::BeginPlay()
{
	Super::BeginPlay();		

	// Enhanced Input 입력 매핑
	if (IsLocalPlayerController())
	{
		// LocalPlayer의 Enhanced Input 시스템 관리자를 가져와 IMC 추가
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(IMC_Default, 0);   // 우선순위 0 (높음)
			}
		}
	}
}
