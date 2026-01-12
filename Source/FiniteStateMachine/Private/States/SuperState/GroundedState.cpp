// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SuperState/GroundedState.h"

#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void UGroundedState::Update(const FStateContext& StateContext)
{
	if (!StateContext.Owner) return;
	
	if (StateContext.Owner->IsGrounded())
	{
		if (StateContext.Owner->IsJumping())
		{
			StateContext.Owner->UseJumpInput();
			_StateMachine->ChangeState(EFSMStateTypes::Jump);
		}
		else if (StateContext.Owner->IsSprinting())
		{
			_StateMachine->ChangeState(EFSMStateTypes::Sprint);
		}
		else if (StateContext.Owner->IsDashing())
		{
			StateContext.Owner->UseDashInput();
			_StateMachine->ChangeState(EFSMStateTypes::Dash);
		}
		else
		{
			_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
		}
	}
	else
	{
		_StateMachine->ChangeState(EFSMStateTypes::InAir);
	}
}
