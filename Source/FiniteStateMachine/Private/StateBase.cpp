// Fill out your copyright notice in the Description page of Project Settings.


#include "StateBase.h"
#include "StateMachineComponent.h"
#include "States/StateTypes.h"


void UStateBase::Initialize(UStateMachineComponent* StateMachine, EFSMStateTypes StateType)
{
	_StateMachine = StateMachine;
	_StateType = StateType;
	StateData = _StateMachine->StateData;
}

void UStateBase::Enter(const FStateContext& StateContext)
{
	UE_LOG(LogTemp, Warning, TEXT("%s - Enter"), *GetStateName());
}

void UStateBase::Update(const FStateContext& Context)
{
	
}

FString UStateBase::GetStateName()
{
	const UEnum* EnumPtr = StaticEnum<EFSMStateTypes>();
	if (!EnumPtr) return TEXT("Invalid State");
	
	return EnumPtr->GetNameStringByValue(static_cast<int64>(_StateType));
}

void UStateBase::Exit()
{
	
}
