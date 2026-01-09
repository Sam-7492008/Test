// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SuperState/AbilityState.h"

#include "StateContext.h"
#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void UAbilityState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (StateContext.Owner->IsGrounded())
	{
		_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
	}
}
