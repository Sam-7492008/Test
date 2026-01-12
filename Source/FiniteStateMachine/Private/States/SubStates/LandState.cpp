// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SubStates/LandState.h"

#include "StateMachineComponent.h"
#include "StateMachineOwner.h"

void ULandState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
}

void ULandState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (StateContext.Owner->GetMovementInput() != FVector2D::ZeroVector)
	{
		_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
	}
	else if (bIsAnimationFinished)
	{
		_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
	}
}
