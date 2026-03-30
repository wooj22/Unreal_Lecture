// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPC.generated.h"


class UInputMappingContext;


UCLASS()
class THIRDPERSON_API ATPSPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// [ Components ]
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInputMappingContext> IMC_Default;


	// [ Lifecycle ]
	virtual void BeginPlay() override;
};
