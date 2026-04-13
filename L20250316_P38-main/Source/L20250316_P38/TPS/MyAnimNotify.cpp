// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"
#include "TPSPlayer.h"

FString UMyAnimNotify::GetNotifyName_Implementation() const
{
	return TEXT("UMyAnimNotify");
}

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference) 
{
	Super::Notify(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotify"));

	ATPSPlayer* Player = Cast<ATPSPlayer>(MeshComp->GetOwner());
	if (Player)
	{
		//->ReloadComplete();
	}
}