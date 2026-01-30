// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SuperState/AbilityState.h"

#include "StateContext.h"
#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void UAbilityState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	bIsAbilityDone = false;
}

void UAbilityState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (bIsAbilityDone)
	{
		if (StateContext.Owner->IsGrounded())
		{
			_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
		}
		else
		{
			_StateMachine->ChangeState(EFSMStateTypes::InAir);
		}
	}
}
