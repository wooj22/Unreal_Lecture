// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"


class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class L20250316_P38_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UFUNCTION()
	void ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UNiagaraSystem> ExplosionTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<USoundBase> ExplosionSound;

	//CPP에서 구현하지 않음
	//BP에서 구현한걸 CPP에서 실행 
	UFUNCTION(BlueprintImplementableEvent)
	void CalculateScore(int InScore);

	//기본은 C++구현을 실행도 C++ 실행, BP에서 재정의 할수 있음
	UFUNCTION(BlueprintNativeEvent)
	void CalculateScoreWithDefault(int InScore);
	void CalculateScoreWithDefault_Implementation(int InScore);

	//이건 구현은 CPP, 호출은 BP
	UFUNCTION(BlueprintCallable, meta=(DisplayName="이건 한글 함수"))
	void ServerCPPFunction();

};
