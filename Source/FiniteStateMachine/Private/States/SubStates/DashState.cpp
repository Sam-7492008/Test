
#include "States/SubStates/DashState.h"

#include "StateContext.h"
#include "StateData.h"
#include "StateMachineOwner.h"

void UDashState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	
	DashStartTime = StateContext.TimeInSeconds;
	lastDashTime = StateContext.TimeInSeconds;
	
	if (StateContext.Owner->IsGrounded())
	{
		StateContext.Owner->PerformDash(StateData->DashStrength);
	}
	else
	{
		StateContext.Owner->PerformDash(StateData->DashStrengthInAir);
	}
}

void UDashState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (StateContext.TimeInSeconds - DashStartTime >= StateData->DashDuration)
	{
		bIsAbilityDone = true;
	}
}

void UDashState::Exit(const FStateContext& StateContext)
{
	Super::Exit(StateContext);
	
	StateContext.Owner->StopDash();
}

bool UDashState::CanDash() const
{
	return GetWorld()->TimeSeconds >= lastDashTime + StateData->DashCooldown;
}

