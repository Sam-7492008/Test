// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SubStates/JumpState.h"

#include "StateContext.h"
#include "StateMachineOwner.h"

void UJumpState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	
	StateContext.Owner->PerformJump();
	bIsAbilityDone = true;
}
