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
	
	StateContext.Owner->StartMovement(_StateMachine->StateData->InAirSpeed);
}
