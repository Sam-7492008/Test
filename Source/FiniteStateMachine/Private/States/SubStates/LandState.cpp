// Fill out your copyright notice in the Description page of Project Settings.


#include "States/SubStates/LandState.h"

#include "StateMachineComponent.h"

void ULandState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	
	_StateMachine->ChangeState(EFSMStateTypes::Locomotion);
}
