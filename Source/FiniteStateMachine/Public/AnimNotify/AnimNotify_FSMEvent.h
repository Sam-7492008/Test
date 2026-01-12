// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMAnimEventType.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FSMEvent.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UAnimNotify_FSMEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSMEvent")
	EFSMAnimEventType EventType;
		
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
