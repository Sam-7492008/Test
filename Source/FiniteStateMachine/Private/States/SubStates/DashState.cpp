
#include "States/SubStates/DashState.h"

#include "StateContext.h"
#include "StateData.h"
#include "StateMachineOwner.h"

void UDashState::Enter(const FStateContext& StateContext)
{
	Super::Enter(StateContext);
	
	DashStartTime = StateContext.TimeInSeconds;
	lastDashTime = StateContext.TimeInSeconds;
	StateContext.Owner->StartDash(StateData->DashDistance);
	bIsAbilityDone = false;
}

void UDashState::Update(const FStateContext& StateContext)
{
	Super::Update(StateContext);
	
	const float Elapsed = StateContext.TimeInSeconds - DashStartTime;
	
	StateContext.Owner->TickDash(StateContext.DeltaTime, StateData->DashDuration, StateData->DashCurve);
	
	if (Elapsed >= StateData->DashDuration)
	{
		StateContext.Owner->StopDash();
		bIsAbilityDone = true;
	}
}

void UDashState::Exit(const FStateContext& StateContext)
{
	Super::Exit(StateContext);
}

bool UDashState::CanDash() const
{
	return GetWorld()->TimeSeconds >= lastDashTime + StateData->DashCooldown;
}

