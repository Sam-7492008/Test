// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SubStates/InAirState.h"

#include "StateContext.h"
#include "StateData.h"
#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void UInAirState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
}

void UInAirState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (StateContext.Owner->IsGrounded())
	{
		_StateMachine->ChangeState(EFSMStateTypes::Land);
	}
	else if (!StateContext.Owner->IsGrounded() && StateContext.Owner->IsDashing())
	{
		StateContext.Owner->UseDashInput();
		_StateMachine->ChangeState(EFSMStateTypes::Dash);
	}
	else
	{
		StateContext.Owner->HandleMovement(_StateMachine->StateData->InAirSpeed);
	}
}
