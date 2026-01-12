
#include "States/SubStates/DashState.h"

#include "StateContext.h"
#include "StateData.h"
#include "StateMachineOwner.h"

void UDashState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	
	DashStartTime = StateContext.TimeInSeconds;
	lastDashTime = StateContext.TimeInSeconds;
	
	StateContext.Owner->PerformDash(StateData->DashStrength);
}

void UDashState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	if (StateContext.TimeInSeconds - DashStartTime >= StateData->DashDuration)
	{
		bIsAbilityDone = true;
	}
}

bool UDashState::CanDash() const
{
	return GetWorld()->TimeSeconds >= lastDashTime + StateData->DashCooldown;
}

