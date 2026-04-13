// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPC.generated.h"


class UInputMappingContext;

/**
 * 
 */
UCLASS()
class L20250316_P38_API ATPSPC : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	virtual void BeginPlay() override;
	
};
