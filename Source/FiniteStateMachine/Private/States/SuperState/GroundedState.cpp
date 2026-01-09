// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SuperState/GroundedState.h"

#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void UGroundedState::Update(const FStateContext& StateContext)
{
	if (!StateContext.Owner) return;
	
	if (!StateContext.Owner->IsSprinting() && StateContext.Owner->IsGrounded())
	{
		_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
	}
	else if (StateContext.Owner->IsSprinting() && StateContext.Owner->IsGrounded())
	{
		_StateMachine->ChangeState(EFSMStateTypes::Sprint);
	}
	else
	{
		//TODO: Trasition to InAir State
	}
}
