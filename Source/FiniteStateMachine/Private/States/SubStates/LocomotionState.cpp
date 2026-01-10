// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SubStates/LocomotionState.h"

#include "StateContext.h"
#include "StateData.h"
#include "StateMachineOwner.h"

void ULocomotionState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
}

void ULocomotionState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	if (!StateContext.Owner) return;
	
	StateContext.Owner->HandleMovement(StateData->MoveSpeed);
	StateContext.Owner->HandleAim();
}
