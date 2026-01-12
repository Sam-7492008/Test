// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_FSMEvent.h"

#include "StateMachineComponent.h"

void UAnimNotify_FSMEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) return;
	
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;
	
	UStateMachineComponent* StateMachineComp = Owner->FindComponentByClass<UStateMachineComponent>();
	
	if (!StateMachineComp) return;
	StateMachineComp->HandleAnimEvent(EventType);
}
