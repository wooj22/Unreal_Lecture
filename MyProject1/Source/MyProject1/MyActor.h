// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

/*
	[ Actor : 미사일 ]
*/

UCLASS()
class MYPROJECT1_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// Components (Replicated)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USoundBase> ExplosionSound;

	// C++에서 선언만 하고 정의는 BP에서 하게 해주는 매크로	
	UFUNCTION(BlueprintImplementableEvent)
	void CalculateScore(int InScore);

	// C++에서 구현하고 실행, BP에서 오버라이드 할 수 있게 해주는 매크로
	UFUNCTION(BlueprintNativeEvent)
	void CalculateScoreWithDefault_Implementation(int InScore);

	// C++에서 구현한 함수를 BP에서 호출할 수 있게 해주는 매크로
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InBPFuntion"))
	void CallCalculateScoreWithDefault(int InScore) { CalculateScoreWithDefault_Implementation(InScore); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Funcs
	void ProcessActorBeginOverlap(AActor* overlapped, AActor* ohterActor);
};
